import os
import sys

pid_fils1 = os.fork()
if pid_fils1 != 1:
    if pid_fils1 == 0:
        print("Je suis le fils1")
    else:
        print("Je suis le père")
        pid_fils2 = os.fork()
        if pid_fils2 != -1:
            print("Je suis le fils2" if pid_fils2 == 0 else "Je suis le père")
        else:
            print("Erreur lors de la création de fils2")
else:
    print("Erreur lors de la création de fils1")
