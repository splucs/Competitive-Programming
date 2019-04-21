contestProperties = {
    "name-1": "",
    "name-2": "",
    "location": "",
    "date": "",
    "timelimit": "2s",
    "memorylimit": "67108864",
    "problem-prefix": ""
}
stopOnFirstError = False
cleanSuffixes = [".exe", ".dcu", ".obj", ".class", ".hi", ".o", ".manifest", ".log", ".in", ".out", ".ans"]
runOptions = [
    "-x", "-t", "2s",
    "-Xacp", "-Xifce",
    "-s", "run.dat", "-o", "t-run.out", "-e", "t-run.err"
]
javaOptions = ["-Xmx1024m", "-Xss64m", "-ea"]
