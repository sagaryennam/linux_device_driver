savedcmd_open_release_driver.mod := printf '%s\n'   open_release_driver.o | awk '!x[$$0]++ { print("./"$$0) }' > open_release_driver.mod
