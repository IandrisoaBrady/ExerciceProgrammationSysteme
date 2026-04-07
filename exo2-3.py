import os
import sys

nb_proc = 5
for i in range(nb_proc):
    pid_fils = os.fork()
    if pid_fils != -1:
        if pid_fils == 0:
            print("Je sus le fils")
            break
        else:
            print("Je suis le père")
    else:
        print("Erreur lors de la création du fils")
