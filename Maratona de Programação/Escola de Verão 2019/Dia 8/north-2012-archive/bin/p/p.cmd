@echo off
set PYTHONPATH=%~dp0..\
@%~dp0..\python\python -b -B -E -s %~dp0p.py %*
