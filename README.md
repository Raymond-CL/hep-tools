# hep-tools

Common tools used in high-energy physics.

At least these at the tools that I commonly use.

Most tools will include an installation script and an example usage code.

It is intented to give newcommers a quick hands-on experience.

| compilers & utilities | generators & simulations | PDF & FF | Analysis & Plot |
| --- | --- | --- | --- |
| [Assembly](README.md#Assembly), [C/C++](README.md#C/C++), [Fortran](README.md#Fortran), [Git](README.md#Git), [HDF5](README.md#HDF5), [HepMC](README.md#HepMC), [Python](README.md#Python), [TeXLive](README.md#TeXLive), [WSL](README.md#WSL) | [MadGraph](README.md#MadGraph), [MCFM](README.md#MCFM), [NLOjet](README.md#NLOjet), [PYTHIA](README.md#PYTHIA) | [LHAPDF](README.md#LHAPDF) |[FastJet](README.md#FastJet), [ROOT](README.md#ROOT) |

## Assembly

Most (legacy) performance computing nowadays are written in Assembly codes.
It is strongly recommended to install the GNU collection of compilers (GCC) and support free software.

## C/C++

Most performance computing nowadays are written in C/C++ codes.
It is strongly recommended to install the GNU collection of compilers (GCC) and support free software.

## FastJet

Algorithm used to cluster partons to jets.

## Fortran

Most (older) performance computing nowadays are written in Fortran codes.
It is strongly recommended to install the GNU collection of compilers (GCC) and support free software.

## Git

For version control, share your code with your collaborators, or just an online backup, Git is your best friend.
It is better to have an editor that has its own GUI-like interface with Git, otherwise it will be painful to just remember those tedious commands.
It may not work in China, but I guess most people use VPN anyways.

## HDF5

Compression algorithm.

## HepMC

This is useless.

## LHAPDF

PDF.

## MadGraph

Another event generator (maybe different shower ordering variable).

## MCFM

A Monte-Carlo (perturbative calculation) for different processes. Not heavy-ion.

## NLOjet

NLO perturbative calculation.

## PYTHIA

Popular event generator for pp collisions.

## Python

This is interesting.

## ROOT

This is a histogram plotter.

## TeXLive

This is compiler for LaTeX codes.

## WSL

In HEP, it is better to work in a Unix-like operating system.
However, since I can't afford a Mac, I will have to run Linux inside Windows OS.
This is where Windows Subsystem for Linux (WSL) comes to the rescue.
The advantage of WSL is, it is fully integrated into Windows, a virtual machine (VM) is not necessary.
The resource kernel is also integrated, you can see your running process from task manager.
I've included a script in *powershell* to install WSL.
