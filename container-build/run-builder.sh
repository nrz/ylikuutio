#!/bin/bash

usage() {
    echo "Usage: ./run-builder.sh [[-r|--recreate] | [-h|--help]]"
    echo
    echo "-r | --recreate   Force recreation of container before building."
    echo "                  This is useful after rebuilding the image."
    echo
    echo "-h | --help       Display this message."
}

CONTAINER_ENGINE="podman"
RECREATE=0

while [ "$1" != "" ]; do
    case "$1" in
        -r | --recreate )   shift
                            recreate=1
                            ;;
        -h | --help )       shift
                            usage
                            exit
                            ;;
        * )                 usage
                            exit 1
    esac
    shift
done

THIS_DIR=$(dirname "$(readlink -f "$0")")
REPO_DIR="$THIS_DIR/.."
BUILD_DIR="$REPO_DIR/build"
# create build directory if it does not exist
[[ ! -e "$BUILD_DIR" ]] && mkdir "$BUILD_DIR"

if [ $RECREATE == 1 ] && "$CONTAINER_ENGINE" container exists ylikuutio-builder; then
    echo "--- Forced recreation, deleting container..."
    "$CONTAINER_ENGINE" container rm ylikuutio-builder > /dev/null
fi

# create container if it does not exist
if ! "$CONTAINER_ENGINE" container exists ylikuutio-builder; then
    echo "--- Creating container..."
    "$CONTAINER_ENGINE" container create \
        --attach stdout \
        --attach stderr \
        --name ylikuutio-builder \
        --cpus $(($(nproc) - 1)) \
        --volume "$BUILD_DIR:/work/build:rw" \
        --volume "$REPO_DIR:/work:ro" \
        ylikuutio-builder \ # image name
        > /dev/null
fi

echo "--- Starting build..."
"$CONTAINER_ENGINE" container start -a ylikuutio-builder
