import os
import os.path
import sys
import shutil
import functools
import platform
import argparse
import hashlib

import util
import languages
import languages_util
import log
import defaults

def findLanguage(program, action, quiet = False):
    lprogram = program.lower()
    if not quiet and not os.path.exists(program):
        raise PException('Cannot {0} "{1}". Program not found.', action, program)

    for language in languages.languages:
        if (
            "file" in language and lprogram == language["file"].lower()
            or "suffix" in language and lprogram.endswith(language["suffix"].lower())
        ): return language
    if quiet:
        from languages_util import noCompile
        return dict(compile = noCompile, run = [])
    raise PException("Cannot {0} {1}. Unsupported type.", action, program)

def findSuffix(program, default = None):
    if os.path.exists(program) and not os.path.isdir(program):
        return program
    lprogram = program.lower()
    for language in languages.languages:
        if ("suffix" in language and os.path.exists(program + language["suffix"])):
            return program + language["suffix"]
    return default if default else program


def loadProperties(filename):
    """
        Loads .properties file into dictionary.
        The values are separated by = symbol.
        Comments lines started with # symbol.
        Names and values are trimmed.
    """
    properties = dict()
    if os.path.exists(filename):
        with open(filename) as file:
            for line in file.readlines():
                if line.strip() != "" and line[0] != "#":
                    (name, value) = line.split("=", 1)
                    properties[name.strip()] = value.strip()
    return properties

def loadContestProperties(filename = "../contest.properties"):
    properties = dict(defaults.contestProperties)
    properties.update(loadProperties(filename))
    return properties

def loadProblemProperties(id = None, filename="problem.properties"):
    if not id:
        id = os.path.basename(os.getcwd())
    properties = dict(id=id, testset="??", solution="??")
    properties.update(loadProperties(filename))
    id = properties["id"]
    defaults = dict(
        input = id + ".in",
        output = id + ".out",
        answer = id + ".ans",
        log = id + ".log",
        source = id,
        checker = properties["testset"],
        alias = id[0].upper(),
        name ="??",
        tests = "##",
    )
    defaults["short-id"] = id[0]
    defaults.update(properties)
    defaults["_tests_format"] = "{{:0{}d}}".format(len(defaults["tests"]))
    return defaults

class PException(Exception):
    def __init__(self, message, *args):
        self.message = message.format(*args)

def executeAndLog(*command):
    util.appendFile("t-run.log", "--- {}", " ".join(command))
    exitcode = util.execute(*command)
    util.concatFiles("t-run.log", "t-run.out", "t-run.err")
    return exitcode

def runCommand(program, args = []):
    program = findSuffix(program)
    return findLanguage(program, "run")["run"](program, list(args))

def logAction(action, problem, test, message, logger):
    logger("{} on problem {} test {}", message, problem["id"], test)
    util.appendFile("t-{}.log".format(action), "{} {}", test, message)

def logActionError(action, problem, test, exitcode):
    logAction(action, problem, test, "Failed to run with exitcode {}".format(exitcode), log.warning)

def runTest(options, action, problem, test, solution):
    inf = "tests/" + test
    log.info("Running {} on problem {} test {}.", solution, problem["id"], test)
    shutil.copyfile(inf, problem["input"])
    util.removeFiles(problem["output"])

    exitcode = time(options, solution)
    if exitcode:
        logActionError(action, problem, test, exitcode)
    return exitcode

def runChecker(action, problem, test):
    ans = "tests/" + test + ".a"
    if not os.path.exists(ans):
        logAction(action, problem, test, "Answer file is not found", log.warning)
        return 1
    if run("Check", problem["input"], problem["output"], ans):
        logAction(action, problem, test, "Check has not accepted solution", log.warning)
        return 1
    logAction(action, problem, test, "Done", log.info)
    return 0

def checkTest(options, problem, test, solution):
    if not os.path.exists("tests/" + test):
        return 0
    return (
        runTest(options, "check", problem, test, solution)
        or runChecker("check", problem, test)
    )

def recursiveDirs():
    return [
        file for file in os.listdir()
        if os.path.isdir(file)
        if not file.startswith("_")
        if not file.startswith(".")
    ]

def recursive(f, test):
    def rec(options):
        if test():
            return f(options)
        log.glob("Scanning {0}", os.getcwd())
        for file in recursiveDirs():
            os.chdir(file)
            exitcode = rec(options)
            os.chdir("..")
            if exitcode:
                return exitcode
        return 0
    return rec

def recWrapper(options, action, description, type, id, f):
    log.glob('{} for {} {} in {}', description, type, id, os.getcwd())
    try:
        exitcode = f(options)
        if exitcode:
            log.warning("{} FAILED FOR {} {}. See t-{}.log.", action.upper(), type.upper(), id, action)
        else:
            log.glob("{} SUCCESSFUL FOR {} {}.", action.upper(), type.upper(), id)
    except PException as e:
        raise PException('{} FAILED FOR {} {}: {}', action.upper(), type.upper(), id, e.message)

def recProblem(action, description, f):
    def wrapper(options):
        problem = loadProblemProperties()
        recWrapper(options, action, description, 'problem', '"' + problem['id'] + '"', f)

    return recursive(wrapper, lambda : os.path.exists("tests") or os.path.exists("Tests.java"))

def recContest(action, description, f):
    def wrapper(options):
        contest = loadContestProperties("contest.properties")
        recWrapper(options, action, description, 'contest', '"' + contest['name-1'] + ", " + contest['name-2'] + '"', f)

    return recursive(wrapper, lambda : os.path.exists("contest.properties"))

def recContestProblem(action, description, contest_f, problem_f):
    def wrapper(options):
        return (recContest(action, description, contest_f)(options)
            or recProblem(action, description, problem_f)(options))
    return wrapper

def runAction(options, action, testAction):
    problem = loadProblemProperties()
    util.removeFiles("t-{}.log".format(action), "t-run.log", "t-run.err", "t-run.out", "run.dat")

    make("check")
    make("interact", quiet = True)

    def resolveSolution(solution, problem):
        if solution == "": return problem["source"]
        if solution == "*": return resolveSolution(problem["solution"], problem)
        if os.path.exists(solution): return solution
        return problem["id"] + "_" + solution

    solution = findSuffix(resolveSolution(options.solution, problem))
    make(solution)

    stopOnFirstError = options.stop_on_first_error or defaults.stopOnFirstError
    exitcode = functools.reduce(
        (lambda success, test :
            (stopOnFirstError and success) or
            testAction(options, problem, test, solution) or success),
        options.test if options.test else testNames(problem),
        0
    )
    if os.path.exists("run.dat"):
        stats = loadProperties("run.dat")
        log.info("MAX TIME IS: {}ms", stats["max.timeConsumed"])
        log.info("MAX MEMORY IS: {:,}B", int(stats["max.memoryConsumed"]))
    util.removeFiles(problem["input"], problem["output"], problem["log"])

    return exitcode

def testNames(problem):
    return [testName(problem, x) for x in range(1, 10 ** len(problem["tests"]))]

def testName(problem, test):
    return problem["_tests_format"].format(test)

def findCheckerAndTests():
    problem = loadProblemProperties()
    def fail(message, *args):
        raise PException("Must build first, {}".format(message), *args)

    def find(name, quiet = False):
        if os.path.exists(name + ".jar"):
            log.info(name + ".jar found")
            return name + ".jar"
        if os.path.exists(name + ".exe"):
            log.info(name + ".exe found")
            return name + ".exe"
        if not quiet:
            fail(name + ".exe/jar is missing.")

    def checkTest(test):
        if not os.path.exists("tests/" + test) and os.path.exists(findSuffix("tests/do" + test)):
            fail("test {} not generated.", test)
        if not os.path.exists("tests/" + test + ".a") and os.path.exists("tests/" + test):
            fail("answer is missing for test {}.", test)
        return os.path.exists("tests/" + test)
    tests = list(filter(checkTest, testNames(problem)))
    for actual, expected in zip(tests, testNames(problem)):
        if actual != expected:
            raise PException("Noncontiguous test set. Test {} is missing", problem["id"], expected)
    if len(tests) == 0:
        fail("no tests found")
    log.info("{} tests found", len(tests))

    return (find("check"), find("interact", quiet = True), tests)

parser = argparse.ArgumentParser(description='Problem manipulation tool.')
parser.add_argument("-v", "--verbose", action="store_true", help="print debug output")
subparsers = parser.add_subparsers(help = 'commands')

def make(*programs, quiet = False):
    for program in programs:
        program = findSuffix(program)
        log.debug("Making {}", program)
        exitcode = findLanguage(program, "make", quiet)["compile"](program)
        if exitcode != 0:
            raise PException('Cannot make "{0}". Exitcode={1}', program, exitcode)
    return 0

def makeDescription():
    langs = [l for l in languages.languages if "suffix" in l]
    suffixes = [l["suffix"] for l in langs]
    scripts = [l["suffix"] for l in langs if l["compile"] == languages_util.noCompile]
    return """
        Makes the specified programs files. Supported extensions are: {}.
        In the later cases ({}) make just silently quits.

        Extension may be omitted. In this case make will try to find the
        file by attaching extensions in the order they are listed above.
        For example, "t make solution" will compile "solution.java" file
        (if it exits) using Java.
    """.format(", ".join(suffixes), ", ".join(scripts))

parser_make = subparsers.add_parser(
    'make',
    aliases = 'm',
    help = 'Makes programs',
    description = makeDescription()
)
parser_make.add_argument('programs', metavar='PROGRAM', nargs='+', help = 'program to make')
parser_make.set_defaults(func = lambda options: make(*options.programs))

def run(program, *args):
    return executeAndLog(*runCommand(program, list(args)))

parser_run = subparsers.add_parser(
    'run',
    aliases = 'r',
    help = 'Runs program',
    description = """
        Runs the specified program (source or executable file). It assumes
        that the source file is already compiled using "make" subcommand
        and uses the corresponding command to run it. For example, "t run
        solution.java" will actually run "java solution", while "t run
        solution.cpp" will actually run "solution.exe". Extension may be
        omitted just like in "make" subcommand.
    """
)
parser_run.add_argument('program', metavar='PROGRAM', help = 'program to run')
parser_run.add_argument('args', metavar='ARG', nargs='*', help = 'program arguments')
parser_run.set_defaults(func = lambda options: run(options.program, *options.args))

def time(options, program, *args):
    command = runCommand(program, args)
    log.debug('Running "{}"', ' '.join(command))

    if findSuffix("interact") != "interact":
        iwrapper = util.relpath("bin\\coact.exe")
        if not os.path.exists(iwrapper):
            raise PException('Cannot run unteractive problem without "coact.exe" wrapper')
        command[0:0] = [iwrapper, "2000", "67108864"] + runCommand("interact")

    x64 = platform.machine() == "AMD64"
    wrapper = util.relpath("bin\\run{}.exe".format("64" if x64 else ""))
    if os.path.exists(wrapper):
        command[0:0] = [wrapper] + defaults.runOptions + ["" if options.output else "-q"]
    return executeAndLog(*command)

parser_time_parent = argparse.ArgumentParser(add_help = False)
parser_time_parent.add_argument("-o", "--output", action="store_true", help = 'show output of run/run64 wrapper')

parser_time = subparsers.add_parser(
    'time',
    aliases = 't',
    help = 'Runs program using "run.exe"',
    description = """
        Works like run subcommand, but execution is wrapped into
        "run.exe" or "run64.exe", if the corresponding wrapper file exists
        in "{}" directory), otherwise
        run is performed directly. It will wrap the run into coact/interact
        pair for interactive problems.
    """.format(util.relpath("")),
    parents = [parser_time_parent]
)
parser_time.add_argument('program', metavar='PROGRAM', help = 'program to run')
parser_time.add_argument('args', metavar='ARG', nargs='*', help = 'program arguments')
parser_time.set_defaults(func = lambda options: time(options, options.program, *options.args))

def problem_check(options):
    return runAction(options, "check", checkTest)

parser_check_parent = argparse.ArgumentParser(add_help = False, parents = [parser_time_parent])
parser_check_parent.add_argument('-s', '--stop-on-first-error', action = 'store_true', help = 'stops checking after first test failed')
parser_check = subparsers.add_parser(
    'check',
    aliases = 'c',
    help = 'Checks solution',
    description = """
        Checks specified solution. It creates "t-check.log" file where outcome
        for each test is listed (one test on a line). Checker program shall be
        named "check" and shall accept "input" "output" and "answer" arguments in this
        order. Works with all available tests unless the list of tests is
        explicitly specified.
    """,
    parents = [parser_check_parent]
)
parser_check.add_argument('solution', metavar='SOLUTION', help = 'solution to check')
parser_check.add_argument('test', metavar='TEST', nargs='*', help = 'test to check on')
parser_check.set_defaults(func = recProblem("check", "Checking problem", problem_check))

def problem_build(options):
    def makeAndRun(program, *args):
        make(program)
        exitcode = run(program, *args)
        if exitcode:
            raise PException("Error running {}. Exitcode={}", program, exitcode)

    def buildTest(options, problem, test, solution):
        if not os.path.exists("tests/" + test): return 0

        exitcode = runTest(options, "build", problem, test, solution)
        if exitcode:
            return exitcode

        shutil.copyfile(problem["output"], "tests/" + test + ".a")
        return runChecker("build", problem, test)

    problem = loadProblemProperties()
    log.info("Generating tests")
    if os.path.exists("Tests.java"):
        makeAndRun("Tests.java")
    else:
        os.chdir("tests")
        if os.path.exists(findSuffix("doall", "~~~")):
            util.removeFiles(*testNames(problem))
            makeAndRun("doall")
        else:
            for test in testNames(problem):
                if findSuffix("do" + test, "~~~") != "~~~":
                    util.removeFiles(test, test + ".a", test + ".b")
                    makeAndRun("do" + test, ">", test)
        os.chdir("..")

    def hashFile(filename):
        with open(filename, "rb") as file:
            return hashlib.sha256(file.read()).hexdigest()

    if options.generate_hashes:
        log.info("Generating test hashes")
        with open("tests.sha256", "wb") as file:
            for test in testNames(problem):
                log.debug("Generating hash for test {}", test)
                if os.path.exists("tests/" + test):
                    file.write((hashFile("tests/" + test) + " tests/" + test).encode("utf8"))
                    file.write(b"\n")
    elif os.path.exists("tests.sha256"):
        log.info("Verifying test hashes")
        for line in util.readLines("tests.sha256"):
            hash, file = line.strip().split(" ")
            log.debug("Verifying hash for test {}", file)
            if hash != hashFile(file):
                raise PException('Hash mismatch for test "{}"', file)
    return runAction(options, "build", buildTest)

parser_build = subparsers.add_parser(
    'build',
    aliases = 'b',
    help = 'Builds test and answer files',
    description = """
        Builds test and answer files. It creates "t-build.log" file
        where outcome for each test is listed (one test on a line). If
        solution is not found, then answer files are not generated. Works
        for all available tests unless the the list of tests is explicitly
        specified. When all tests are being built it also compiles checker
        program named "check" if it exists.
        If "tests.sha256" file exists, check test hashcodes against it.
        This file could be generated by specifying "-g" option.
    """,
    parents = [parser_check_parent]
)
parser_build.add_argument('solution', metavar='SOLUTION', help = 'solution forgenerating answers')
parser_build.add_argument('test', metavar='TEST', nargs='*', help = 'tests to generate andswers for')
parser_build.add_argument('-g', '--generate-hashes', action='store_true', help = 'generate test hashes')
parser_build.set_defaults(func = recProblem("build", "Building problem", problem_build))



def contest_xml(options):
    contest = loadContestProperties("contest.properties")
    body = "\n    ".join([
        '<problem-ref id = "{short-id}" alias = "{alias}" problem-id = "{id}" name = "{name}"/>'.format(**loadProblemProperties(file, file + "/problem.properties"))
        for file in os.listdir() if os.path.isdir(file) if not file.startswith("_") and not file.startswith(".")
    ])
    util.writeFile("challenge.xml", """
<challenge
    id              = "{id}"
    name            = "{name-1}, {name-2}"
    scoring-model   = "%icpc"
    length          = "5h"

    problem-id      = "{problem-prefix}"
    xmlai-process   = "http://neerc.ifmo.ru/develop/pcms2/xmlai/default-rules.xml"
>
    {body}
</challenge>""".format(body = body, **contest)
    )
    return 0

def problem_xml(options):
    problem = loadProblemProperties()
    contest = loadContestProperties()

    if options.time_limit:
        contest["timelimit"] = options.time_limit
    if options.memory_limit:
        contest["memorylimit"] = options.memory_limit
    if options.prefix:
        contest["problem-prefix"] = options.prefix

    util.removeFiles("problem.xml")

    prefix = contest["problem-prefix"]
    prefix = prefix if prefix == "" or prefix.endswith(".") else prefix + "."

    checker, interact, tests = findCheckerAndTests()
    checkerLine = (
        '<binary executable-id = "java.check" file = "check.jar"/>'
        if checker.lower() == "check.jar"
        else '<binary executable-id = "x86.exe.win32" file = "check.exe"/>'
    )
    util.writeFile("problem.xml", """
<problem
    id      = "{id}"
    version = "1.0"
>
    <judging>
        <script type = "%icpc">
            <testset
                test-count   = "{testNumber}"
                input-href   = "tests/{tests}"
                answer-href  = "tests/{tests}.a"
                input-name   = "{input}"
                output-name  = "{output}"
                time-limit   = "{timelimit}"
                memory-limit = "{memorylimit}"
            />
            <verifier type = "%testlib">
                {checkerLine}
            </verifier>
        </script>
    </judging>
</problem>""".format(
        id = prefix + problem["id"],
        checkerLine = checkerLine,
        timelimit = (problem if hasattr(problem, "timelimit") else contest)["timelimit"],
        memorylimit = (problem if hasattr(problem, "memorylimit") else contest)["memorylimit"],
        testNumber = len(tests),
        tests = problem["tests"],
        input = problem["input"],
        output = problem["output"]
    ))
    return 0

parser_xml = subparsers.add_parser(
    'xml',
    aliases = 'x',
    help = 'Builds "challenge.xml" and "problem.xml"',
    description = """
        Builds "challenge.xml" and "problem.xml", so that contest (problem)
        can be used with PCMS2-v2 contest management system. You must
        successfully use "build" subcommand before using xml subcommand.
        Prefix is prepended to problem identifiers (default is empty).
        Default time limit is 2s, memory limit 67108864.
    """,
)
parser_xml.add_argument("-p", "--prefix", help = "problem prefix")
parser_xml.add_argument("-t", "--time-limit", help = "contest time limit (default {})".format(defaults.contestProperties["timelimit"]))
parser_xml.add_argument("-m", "--memory-limit", help = "contest memory limit (default {})".format(defaults.contestProperties["memorylimit"]))
parser_xml.set_defaults(func = recContestProblem("xml", "Building XML", contest_xml, problem_xml))



def contest_pcms(options):
    contestDir = util.relswd(options.directory)
    util.cleanDirs(contestDir)

    if not os.path.exists("challenge.xml"):
        raise PException('Must run "xml" first, challenge.xml not found')
    util.copyToDir("challenge.xml", contestDir)
    return 0

def problem_pcms(options):
    problem = loadProblemProperties()
    problemDir = util.relswd(options.directory) + "/" + problem["id"] + "/"
    util.cleanDirs(problemDir, problemDir + "/tests")

    if not os.path.exists("problem.xml"):
        raise PException('Must run "xml" first, problem.xml not found')
    util.copyToDir("problem.xml", problemDir)

    checker, interact, tests = findCheckerAndTests()
    util.copyToDir(checker, problemDir)
    if interact: util.copyToDir(interact, problemDir)

    for test in tests:
        util.copyToDir("tests/" + test, problemDir)
        util.copyToDir("tests/" + test + ".a", problemDir)

    for name in ["Check", "Interact"]:
        file = findSuffix(name)
        if os.path.exists(file):
            log.info(file + " found")
            util.copyToDir(file, problemDir)

    bannerSpecial(problemDir, "Check", "Checker", "checker")
    bannerSpecial(problemDir, "Interact", "Interactor", "interact")
    banner(problemDir, languages_util.comments_xml, "problem.xml")

    return 0

parser_pcms = subparsers.add_parser(
    'pcms',
    aliases = 'p',
    help = 'Copies PCMS configuration files and tests to "__pcms" directory',
    description = """
        Copies PCMS configuration files (chellenge.xml, problem.xml, tests,
        checker) to the specified directory. You must successfully use "build"
        and "xml" subcommand before using pcms subcommand.
    """,
)
parser_pcms.add_argument("-d", "--directory", help = "directory to write result to")
parser_pcms.set_defaults(func = recContestProblem("pcms", "Building PCMS", contest_pcms, problem_pcms), directory = "__pcms")



def banner(problemDir, comments, file, type = None, author = None):
    contest = loadContestProperties()
    problem = loadProblemProperties()
    if type and not author:
        author = file.split(".")[0].split("_")[1]
    line = comments["begin"] + comments["line"] * 64 + comments["end"]

    def text(format, *args):
        return comments["begin"] + " " + format.format(*args).ljust(63) + comments["end"]

    def multiline(name, property):
        result = []
        for author in map(expand, problem[property].split(" ")):
            result += [aligned(name, author)]
            name = ""
        return result

    def aligned(name, value):
        return text("{:<21} {}", name, value)

    def expand(author):
        if not "juror." + author in contest:
            raise PException('Cannot find juror "{}"', author)
        return contest["juror." + author]

    util.writeFile(problemDir + file, "{}", "\n".join([
            line,
            text("{}", contest["name-1"]),
            text("{}", contest["name-2"]),
            text("{}", contest["location"] + ", " + contest["date"]),
            line,
            text("Problem {}. {}",  problem["alias"], problem["name"]),
            text("")
        ]
        + multiline("Original idea", "idea")
        + multiline("Problem statement", "statement")
        + multiline("Test set", "testset")
        + ([
            line,
            text("{}", type),
            text(""),
            aligned("Author", expand(author)),
        ] if type else []) + [
        line,
        "",
        "",
        ]) + "".join(util.readLines(file)))

def bannerSpecial(problemDir, program, type, property):
    problem = loadProblemProperties()
    try:
        program = findSuffix(program)
        banner(problemDir, findLanguage(program, "archive")["comments"], program, type, problem[property])
    except PException:
        pass

def problem_archive(options):
    problem = loadProblemProperties()
    contest = loadContestProperties()

    problemDir = util.relswd(options.directory) + "/" + problem["id"] + "/"
    util.cleanDirs(problemDir)

    if not os.path.exists("problem.xml"):
        raise PException('Must run "xml" first, problem.xml not found', problem["id"])

    checker, interact, tests = findCheckerAndTests()

    bannerSpecial(problemDir, "Check", "Checker", "checker")
    bannerSpecial(problemDir, "Interact", "Interactor", "interact")
    bannerSpecial(problemDir, "Tests", "Tests", "testset")
    banner(problemDir, languages_util.comments_xml, "problem.xml")

    if os.path.exists("tests.sha256"):
        util.copyToDir("tests.sha256", problemDir)

    for language in filter(
        lambda l: "suffix" in l and "comments" in l and l["comments"],
        languages.languages
    ):
        for file in os.listdir():
            if file.endswith(language["suffix"]) and file.find("_") != -1:
                options.solution = file
                options.test = None
                try:
                    if (not problem_check(options)):
                        log.info("Copying solution {} to archive", file)
                        banner(problemDir, language["comments"], file, "Solution")
                except PException as e:
                    log.warning(e.message)

    return 0

parser_archive = subparsers.add_parser(
    'archive',
    aliases = 'a',
    help = 'Creates official archive',
    description = """
        Copies correct solutions, checkes, test generators, etc into a
        "__archive" directory. All files are prepended with contest banners.
        You must successfully use "build" and "xml" subcommand before using
        archive subcommand.
    """,
    parents = [parser_check_parent]
)
parser_archive.add_argument("-d", "--directory", help = "directory to write result to")
parser_archive.set_defaults(func = recProblem("archive", "Creating archive", problem_archive), directory = "__archive")



def problem_examples(options):
    problem = loadProblemProperties()
    statementsFile = options.statements + "/" + problem["id"] + ".tex"
    if not os.path.exists(statementsFile):
        raise PException('Statements "{}" not found ', problem["id"], statementsFile)

    checker, interact, tests = findCheckerAndTests()

    def unescapeTex(line):
        return (
            line
            .replace("\~", "---###TILDE###---")
            .replace("~", "")
            .replace("$\\sim$", "~")
            .replace("{}", "")
            .replace("\\\\", "---###SLASH###---").replace("\\", "").replace("---###SLASH###---", "\\")
            .replace("---###TILDE###---", "~")
        )

    tests = 0
    state = ["none"]
    input = []
    output = []
    for rline in util.readLines(statementsFile):
        line = rline.strip()
        if state[0] == "none":
            if line == "\\exmp{":
                tests += 1
                state[0] = "input"
                input[0:len(input)] = []
        elif state[0] == "input":
            if line == "}{":
                state[0] = "output"
                output[0:len(output)] = []
                if input != util.readLines("tests/" + testName(problem, tests)):
                    raise PException('EXAMPLES FAILED FOR PROBLEM {}. Example input {} is not equal to test.',
                        problem["id"], tests)
            else:
                input += [unescapeTex(rline)]
        elif state[0] == "output":
            if line == "}" or line == "}%":
                state[0] = "none"
                util.writeFile("__output", "{}", "".join(output))
                if run("Check", "tests/" + testName(problem, tests),  "__output", "tests/" + testName(problem, tests) + ".a".format(tests)):
                    raise PException('EXAMPLES FAILED FOR PROBLEM {}. Example output {} rejected by checker.',
                        problem["id"], tests)
                util.removeFiles("__output")
            else:
                output += [unescapeTex(rline)]
    if state[0] != "none":
        raise PException('Invalid examples murkup.')
    if tests == 0:
        raise PException('No examples found.')
    return 0

parser_examples = subparsers.add_parser(
    'examples',
    aliases = 'e',
    help = 'Checks examples from problem statements',
    description = """
        Extracts sample inputs and output from problem statements.
        Compares first tests from testset and extracted sample inputs.
        Run checker to verify the correctness of sample outputs.
        You must successfully use "build" subcommand before using examples subcommand.
    """
)
parser_examples.add_argument('statements', metavar='STATEMENTS', help = 'problem statements directory')
parser_examples.set_defaults(func = recProblem("examples", "Checking examples", problem_examples))




def contest_clean(options):
    util.removeFiles("challenge.xml")
    return 0

def problem_clean(options):
    problem = loadProblemProperties()

    if os.path.exists(findSuffix("tests/doall")):
        for test in testNames(problem):
            util.removeFiles("tests/" + test)
    if findSuffix("Tests") != "Tests":
        util.removeDirs("tests")
    for test in testNames(problem):
        if os.path.exists(findSuffix("tests/do" + test)):
            util.removeFiles("tests/" + test)

    util.removeFiles("tests.jar", "check.jar", "validator.jar", "interact.jar")

    util.removeFiles(*
        ["tests/" + test + ".a" for test in testNames(problem)] +
        ["tests/" + test + ".b" for test in testNames(problem)]
    )
    util.removeFiles(*[
        dir + "/" + filename
        for dir in filter(os.path.exists, [".", "tests"])
        for filename in os.listdir(dir)
        for suffix in defaults.cleanSuffixes
        if filename.endswith(suffix)
    ])
    util.removeFiles("run.dat", "problem.xml", "t-run.err")

    return 0

parser_clean = subparsers.add_parser(
    'clean',
    aliases = 'e',
    help = 'Cleans contest and problem directories',
    description = """
        Cleans all auxiliary files that might have been created during "build",
        "xml", and "check" operations.
    """
)
parser_clean.set_defaults(func = recContestProblem("clean", "Cleaning directory", contest_clean, problem_clean))



def problem_validate(options):
    problem = loadProblemProperties()
    make("Validator")

    checker, interact, tests = findCheckerAndTests()
    for test in tests:
        exitcode = runTest(options, "validate", problem, test, "Validator")
        if exitcode:
            raise PException("Validator exit code {}", exitcode)

    return 0

parser_validate = subparsers.add_parser(
    'validate',
    aliases = 'v',
    help = 'Validates tests',
    description = """
        Checks that "validator" solution runssuccesfully on each test.
        Validator output is discarded. You must successfully use "build"
        subcommand before using examples subcommand.
    """,
    parents = [parser_time_parent]
)
parser_validate.set_defaults(func = recProblem("validate", "Validate tests", problem_validate))



def input(options):
    problem = loadProblemProperties()
    inf = "tests/" + testName(problem, int(options.test))
    if not os.path.exists(inf):
        raise PException('File "{}" not found', inf)
    if not os.path.exists(inf + ".a"):
        raise PException('File "{}.a" not found', inf)
    shutil.copyfile(inf, problem["input"])
    shutil.copyfile(inf + ".a", problem["answer"])
    return 0

parser_input = subparsers.add_parser(
    'input',
    aliases = 'i',
    help = 'Copies test file',
    description = """
        Copies specified test and answer files from testset.
    """
)
parser_input.add_argument('test', metavar='TEST', help = 'test to copy')
parser_input.set_defaults(func = input)




if __name__ == "__main__":
    try:
        options = parser.parse_args(sys.argv[1:])
        util.options = options
        exit(options.func(options))
    except PException as e:
        log.error(e.message)
        util.writeFile("t.out", e.message)
        exit(1)
    except KeyboardInterrupt:
        log.warning("Interrupted by ^C")
        exit(1)
    except WindowsError as e:
        log.error("SYSTEM ERROR: {}", str(e))
        exit(1)
