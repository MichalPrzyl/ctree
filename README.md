# SFL - Simplified file system

<div align='center'>
     <img src="SFL_1.png" width='800'>
</div>

Project is minimal, simplified file system written in pure C.
Everything is in-memory.
It imitates unix-like filesystem with tree-structured data/file system.
It implements basic commands like `cd` (change directory), `touch` (create file), `ls`, `pwd`, `mkdir`.

# Purpose
Just educational.
- Understanding trees and their implementation
- knowledge about pointers and memory management
- integrating that knowledge with unix-like mindset and understanding of how shell works with paths/filesystems

# Core concepts

The filesystem is implemented as a tree of nodes. Each node represents file or directory. Every node has exactly one parent. There is root `/` directory which has no parent. It's built-in.

```
/
└── home
    └── user
        ├── notes.txt
        ├── games.txt
        └── secret.txt
```


# TODO
There are so much more to implement in that project, for example:
- more commands/programs/utilities
- reading files
- editing files
- autocompletion
- colors
- flags (for instance `ls -al`)
- clearing
- better parsing
- and basically sky is the limit