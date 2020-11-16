# Building Ylikuutio in a container

These instructions and the accompanied script currently assume the Podman container engine,
but Docker should work with relatively few modifications.

Depending on the container runtime configuration in your system,
you may have to run these commands as root.
Either run all commands with root or all commands as regular user!

1. Make sure you have Podman installed in your system.
2. Build the image: `podman build -t ylikuutio-builder .`
3. Build Ylikuutio using the provided script: `./run-builder.sh`
   * As with Podman, you may have to run this script as root as well.
4. The resulting files will be located in the `../build` directory. If you ran Podman as root, the files will be owned by root.

## Subsequent builds

* As you make modifications to the code of the engine, you will only need to rerun step 3 of this procedure.
* If you wish to add or remove dependencies, you must rebuild the container image (step 2),
  then run step 3 with the command line option `--recreate` to recreate the container from the updated image.

## Removing containers and images left behind

If you find that building in containers is not for you, you may remove the image and container created in the
above steps with these commands:

1. `podman container rm ylikuutio-builder`
2. `podman image rm ylikuutio-builder`
