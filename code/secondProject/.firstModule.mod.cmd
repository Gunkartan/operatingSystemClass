savedcmd_firstModule.mod := printf '%s\n'   firstModule.o | awk '!x[$$0]++ { print("./"$$0) }' > firstModule.mod
