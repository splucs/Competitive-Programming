import os
from languages_util import *
import defaults
import util

def runTests(run):
    util.removeDirs("tests")
    os.mkdir("tests")
    return run()

languages = [
    javaSpecial(
        "tests",
        "Java-based test generator",
        run = runTests
    ),
    javaSpecial(
        "validator",
        "Java-based test validator",
        [util.relpath("testlib\\testlib4j.jar"), util.relpath("testlib")]
    ),
    javaSpecial(
        "check",
        "Java-based checker",
        [util.relpath("testlib\\testlib4j.jar")],
        addArgs = ["ru.ifmo.testlib.CheckerFramework"]
    ),
    javaSpecial("check", "Java-based checker"),
    compiled(".java", "Java", comments_c,
        ["javac", "-cp", ".", "{program}"],
        addArgs(lambda program : java(util.deleteSuffix(program), ["."]))
    ),
    compiled(".dpr", "Borland Delphi", comments_pascal,
        ["dcc32", "-m", "-cc", "-U" + util.relpath("testlib"), "{program}"]
    ),
    compiled(".c", "C", comments_c,
        ["cl", "/O2", "-I" + util.relpath("testlib"), "{program}"],
        tempSuffixes = [".obj"]
    ),
    compiled(".cpp", "C++", comments_c,
        ["cl", "/O2", "/EHsc", "-I" + util.relpath("testlib"), "{program}"],
        tempSuffixes = [".obj"]
    ),
    compiled(".c++", "C++", comments_c, [
        "g++", "-O2", "-Wl,--stack=67108864", "{program}",
        "-I" + util.relpath("testlib"),
        "-o", "{programNoSuffix}.exe",
    ]),
    compiled(".cs", "C#", comments_c,
        ["csc", "/o", "/platform:x86", "{program}"]
    ),
    compiled(".vb", "Visual Basic", comments_basic,
        ["vbc", "/platform:x86", "{program}"]
    ),
    compiled(".hs", "Haskell", comments_haskell,
        ["ghc", "--make", "{program}"]
    ),
    compiled(".ml", "OCaml", comments_pascal,
        ["ocamlopt", "{program}", "-o", "{programNoSuffix}.exe"]
    ),
    script(".py", "Python", comments_python,
        ["python", "{program}"]
    ),
    script(".cmd", "Windows command interpreter", comments("rem #", "#", "#"),
        ["cmd", "/c", "{program}"]
    ),
    script(".exe", "Windows executable", None,
        ["{program}"]
    ),
    dict(
        suffix = ".class",
        description = "Java .class files",
        compile = noCompile,
        run = addArgs(lambda program: java(util.deleteSuffix(program), ["."]))
    )
]
