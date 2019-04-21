import util
import os

import defaults

def runExe(program, args):
    return [util.replaceSuffix(program, ".exe")] + args

def noCompile(program):
    return 0

def joinClasspath(classpath):
    return ";".join(classpath)

def java(className, classpath = ["."], args = []):
    return _java(classpath, [className] + args)

def _java(classpath = ["."], args = []):
    return ["java"] + defaults.javaOptions + ["-cp", joinClasspath(classpath)] + list(args)

def _run(run):
    return run()

def javaSpecial(name, description, addClasspath = [], addArgs = [], run = _run):
    def classpath():
        return [name + ".jar"] + addClasspath + [
            "lib/" + filename
            for filename in util.listdir("lib/")
            if filename.lower().endswith(".jar")
        ]

    def javac(program):
        temp = "__" + name
        util.removeDirs(temp)
        try:
            util.removeFiles(name + ".jar")
            os.makedirs(temp)
            return util.execute("javac",
                "-sourcepath", ".",
                "-d", temp,
                "-cp", joinClasspath(classpath()),
                program
            ) or util.execute("jar", "cf", name + ".jar", "-C", temp, ".")
        finally:
            util.removeDirs(temp)

    return dict(
        file = name.title() + ".java",
        description = description,
        comments = comments_c,
        compile = javac,
        run = (lambda program, args: run(lambda: _java(classpath(), addArgs + [util.deleteSuffix(program)] + args)))
    )

def addArgs(f):
    return (lambda program, args: f(program) + args)

def substituteProgram(program, command):
    return [
        c.format(program = program, programNoSuffix = util.deleteSuffix(program))
        for c in command
    ]

def compiled(suffix, description, comments, compileCommand, run = runExe, tempSuffixes = []):
    def compile(program):
        try:
            return util.execute(*substituteProgram(program, compileCommand))
        finally:
            util.removeFiles(*[util.replaceSuffix(program, suffix) for suffix in tempSuffixes])

    return dict(
        suffix = suffix,
        description = description,
        comments = comments,
        compile = compile,
        run = run
    )

def script(suffix, description, comments, runCommand):
    return dict(
        suffix = suffix,
        description = description,
        comments = comments,
        compile = noCompile,
        run = addArgs(lambda program: substituteProgram(program, runCommand))
    )

def comments(begin, line, end):
    return dict(begin = begin, line = line, end = end)

comments_c = comments("/*", "*", "*/")
comments_pascal = comments("(*", "*", "*)")
comments_haskell = comments("{-", "-", "-}")
comments_xml = comments("<!--", "=", "-->")
comments_basic = comments("'", "=", "'")
comments_python = comments("#", "#", "#")
