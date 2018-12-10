# Advent of Code 2018

This repo contains solutions for the AOC 2018 exercises.

A note on how I developed these: 

using the included Dockerfile:
`docker build -t . cpp:latest`

Then run the docker like zo:
`docker run -v "${PWD}:/code" -it cpp:latest bash`

This will give you a shell into the container.

If it's a first time run (either starting from nothing, or adding new files) then do `cmake .` inside the container.

Then run `make && ./AdventOfCodeTest` to run all tests, or run `make && day-${n}/test` for a specific day n.
