Ins

OpenMP2Parallel
==========

Custom bootstrap installation and configuration for Mac. Kind of a "dotfiles
repo" too.

<br />
Introduction
============

The presented tools are Source to Source compilers (S2S) based on BSC's [Mercurium Framework](https://pm.bsc.es/mcxx)[1]. Mercurium is a source-to-source compilation infrastructure aimed at fast prototyping and supports C and C++ languages and is mainly used in Nanos environment to implement OpenMP but since it is quite extensible it has been used to implement other programming models or compiler transformations. This framework is used in order to implement our S2S transformation phases, providing us with the Abstract Syntax Tree(AST) as an easy access to the table of symbols. This information is analyzed through our set of tools to parse and translate the original problem to an optimum version of target language.

* **OMP2HMPP**[2], a tool that, automatically translates a high-level C source code(OpenMP) code into HMPP. The generated version rarely will differs from a hand-coded HMPP version, and will provide an important speedup, near 113%, that could be later improved by hand-coded CUDA.

* **OMP2MPI**, currently in development phase...


[1] J. Balart, A. Duran, M. Gonzalez, X. Martorell, E. Ayguade, and J. Labarta. Nanos mercurium: a research compiler for openmp. In Proceedings of the European Workshop on OpenMP, volume 8, 2004.

[2] Albert Saa-Garriga, David Castells-Rufas, and Jordi Carrabina. 2014. OMP2HMPP: HMPP Source Code Generation from Programs with Pragma Extensions. In High Performance Energy Efficient Embedded Systems. ACM.

Installation
============

Easy peasy:


	1. git clone git://github.com/sdruix/OpenMP2Parallel.git ~/.mcxx
	2. cd ~/.mcxx && ./configure [--prefix=path/to/set] --enable-tl-openmp-profile
  3. make
  4. [sudo] make install
  5. For OMP2HMPP execution: omp2hmpp [-h] 

Pay attention to the installation/configuration process because some questions will be asked. Sometimes easy ones as your Github user/email, sometimes more difficult ones as your root credentials to be able to proceed!

Relative to my work, I'd like to share it with the world under an simple clause: If you use it the least you must choose something from this list.

* Make any constructive comment of my code. I'm here to learn.
* Contribute something to this scripts. Updates, fixes, features... Whatever!

Besides that, I hope you are kind enough to reference any your sources whether is my code or a code from a 3rd party!

