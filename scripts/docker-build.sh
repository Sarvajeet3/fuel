#!/bin/sh

docker build --platform=linux/amd64 -t ubuntu18-x86_64 .
docker build --platform=linux/arm64 -t ubuntu18-arm64 .
docker build --platform=linux/arm/v7 -t ubuntu18-arm32 .
