import os
import sys

pid = os.fork()

if pid != -1:
    print("Je suis le fils" if pid == 0 else "Je suis le père")
else:
    print("Erreur lors de la création du processus fils")
    sys.exit(1)
