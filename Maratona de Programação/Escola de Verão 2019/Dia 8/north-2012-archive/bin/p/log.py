import colorama
import util

colorama.init(autoreset=True)

def colored(color):
    return lambda message, *args: print(color + message.format(*args))

error = colored(colorama.Fore.RED)
warning = colored(colorama.Fore.YELLOW)
glob = colored(colorama.Fore.GREEN)
info = colored(colorama.Fore.CYAN)
def debug(message, *args):
    if (util.options.verbose):
        colored("")(message, *args)
