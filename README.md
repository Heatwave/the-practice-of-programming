# The Practice of Programming

_The Practice of Programming_ by Brian W. Kernighan and Rob Pike

## Chapter 1: Style

### 1.1 Names

1. The broader the scope of a variable, the more information should be conveyed by its name.
1. Use descriptive names for globals, short names for locals.
1. Be consistent. Give related things related names that show their relationship and highlight their difference.
1. Use active names for functions. Function names should be based on active verbs, perhaps followed by nouns.
1. Be accurate. A name not only labeled, it conveys information to the reader. A misleading name can result in mystifying bugs.

### 1.2 Expressions and Statements

1. Indent to show structure. A consistent indentation style is the lowest-energy way to make a program's structure self-evident.
1. Use the natural form for expressions. Conditional expressions that include negations are always hard to understand.
1. Break up complex expressions.
1. Be clear. Write clear code, not clever code.
1. Be careful with side effects. Like the operator ++.

### 1.3 Consistency and Idioms

1. Use a consistent indentation and brace style.
1. Use idioms for consistency.
1. Use else-if for multi-way decisions.

### 1.4 Function Macros

1. Avoid function macros.
1. Parenthesize the macro body and arguments.

### 1.5 Magic Numbers

1. Give names to magic numbers.
1. Define numbers as constants, not macros. Use final in Java.
1. Use character constants, not integers.
1. Use the language to calculate the size of an object.

### 1.6 Comments

1. Don't belabor the obvious.
1. Comment functions and global data.
1. Don't comment bad code, rewrite it.
1. Don't contradict the code.
1. Clarity, don't confuse.

### 1.7 Why Bother?

## Chapter 2: Algorithms and Data Structures

### 2.1 Searching

1. Sequential search. Also known as linear search.
1. Binary search. For a larger sorted array.
1. [2.1.binary-search.c](2.1.binary-search.c)

### 2.2 Sorting

1. quicksort:

    ```text
    pick one element of the array (the "pivot")  
    partition the other element into two groups:  
        "little ones" that are less than the pivot value, and  
        "big ones" that are greater than or equal to the pivot value.  
    recursively sort each group.  
    ```

1. Average time complexity: O(n㏒n)
1. [2.2.quick-sort.c](2.2.quick-sort.c)

### 2.3 Libraries

1. ANSI C library:
    1. qsort: [2.3.libraries-qsort.c](2.3.libraries-qsort.c)
    1. bsearch: [2.3.libraries-bsearch.c](2.3.libraries-bsearch.c)
1. It's a good idea to use "bsearch" instead of writing your own.
1. Over the years, binary search has proven surprisingly hard for programmers to get right.
1. [Exercise-2-1.quicksort-iteratively.c](Exercise-2-1.quicksort-iteratively.c)

### 2.4 A Java Quicksort

1. [Quicksort.java](java/src/org/the/practice/of/programming/quicksort/Quicksort.java)

### 2.5 O-Notation

Notation | Name | Example
------------ | ------------- | -------------
O(1) | constant | array index
O(logn) | logarithmic | binary search
O(n) | linear | string comparison
O(nlogn) | nlogn | quicksort
O(n²) | quadratic | simple sorting methods
O(n³) | cubic | matrix multiplication
O(2^n) | exponential | set partitioning

1. [Exercise-2-3.quicksort-experiment.c](Exercise-2-3.quicksort-experiment.c)
1. [Exercise-2-4.slowsort.c](Exercise-2-4.slowsort.c)

### 2.6 Growing Arrays

1. [2.6.growing-arrays.c](2.6.growing-arrays.c)

### 2.7 Lists

1. [2.7.lists.c](2.7.lists.c)
1. [Exercise-2-9.generic-list.c](Exercise-2-9.generic-list.c)

### 2.8 Trees

1. Many operations that take time O(n) in lists or arrays require only O(logn) time in trees.
1. A tree in which each path from the root to the leaf has approximately the same length is called _balanced_. The advantage of a balanced tree is that searching it for an item is an O(logn) process, since, as in binary search, the number of possibilities is halved at each step.
1. Realistically, binary search trees are infrequently used, though B-trees, which have very high branching, are used to maintain information on secondary storage.
1. parse tree.
1. [2.8.trees.c](2.8.trees.c)

### 2.9 Hash Tables

1. Empirically, the values 31 and 37 have proven to be good choices for the multiplier in a hash function for ASCII strings.
1. [2.9.hash-tables.c](2.9.hash-tables.c)

### 2.10 Summary

1. Each operation has an expected computation time that often determines how suitable this data type (or implementation) is for a particular application.
1. Arrays support constant-time access to any element but do not grow or shrink gracefully.
1. Lists adjust well to insertions and deletions, but take O(n) time to access random elements.
1. Trees and hash tables provide a good compromise: rapid access to specific items combined with easy growth, so long as some balance criterion is maintained.
1. There are other more sophisticated data structures for specialized problems, but this basic set is sufficient to build the great majority of software.

## Chapter 3: Design and Implementation

1. The design of the data structures is the central decision in the creation of a program.
1. One aspect of this point of view is that the choice of programming language is relatively unimportant to the overall design.

### 3.1 The Markov Chain Algorithm

1. A Markov chain algorithm emits output phrases by randomly choosing the suffix that follows the prefix, according to the statistics of (in our case) the original text.
1. Three-word phrases work well-a two-word prefix is used to select the suffix word:

    ```text
    set w1 and w2 to the first two words in the text
    print w1 and w2
    loop:
        randomly choose w3, one of the successors of prefix w1 w2 in the text
        print w3
        replace w1 and w2 by w2 and w3
        repeat loop
    ```

### 3.2 Data Structure Alternatives

1. The Markov algorithm must see all the input before it can begin to generate output, so it must store the entire input in some form.
1. Because we want the input broken down into words, so we won't store it in a long string.
1. If we store it as an array of pointers to words, we need to scan the array to see what possible suffix words follow the prefix. 1,000 words of output means hundreds of millions of string comparisons, which will not be fast.
1. We need a data structure that better represents a prefix and its associated suffixes.
1. For purposes of description, we'll assume a two-word prefix, so each output word is based on the pair of words that precede it.
1. Given a prefix, we need to store all the suffixes that follow it so we can access them later.
1. If a phrase appears more than once, we just adding it more than once in the suffix list. Since adding a suffix doesn't require checking whether it's there already, and experiments showed that the difference in run-time was negligible.
1. In summary each state comprises a prefix and a list of suffixes. This information is stored in a hash table, with prefix as key. Each prefix is a fixed-size set of words. If a suffix occurs more than once for a given prefix, each occurrence will be included separately in the list.
1. Since most text has many words appearing multiple times, it would probably save storage if we kept a second hash table of single words, so the text of each word was stored only once.

### 3.3 Building the Data Structure in C

1. [3.3.markov-chain.c](3.3.markov-chain.c)

### 3.4 Generating Output

1. [Exercise-3-3.markov-chain-second-hash-table.c](Exercise-3-3.markov-chain-second-hash-table.c)
1. [Exercise-3-4.markov-chain-without-sentinel.c](Exercise-3-4.markov-chain-without-sentinel.c)

### 3.5 Java

1. The Java program is significantly smaller than the C program and takes care of more details; _Vectors_ and the _Hashtable_ are the obvious examples.
1. In general storage management is easy since vectors grow as needed and garbage collection takes care of reclaiming memory that is no longer referenced.
1. But to use the _Hashtable_ class, we still need to write functions hashCode and equals, so Java isn't taking care of all the details.
1. Comparing the way the C and Java programs represent and operate on the same basic data structure, we see that the Java version has better separation of functionality. For example, to switch from _Vectors_ to arrays would be easy.
1. In the C version, everything knows what everything else is doing: the hash table operates on arrays that are maintained in various places, **lookup** knows the layout of the **State** and **Suffix** structures, and everyone knows the size of the prefix array.
1. [Markov.java]()

### 3.6 C++

1. Since C++ is almost a superset of C, it can be used as if it were C with a few notational conveniences, and our original C version of _markov_ is also a legal C++ program.
1. A more appropriate use of C++, however, would be to define classes for the objects in the program, more or less as we did in Java; this would let us hide implementation details.
1. We decided to go even further by using the Standard Template Library or STL.
1. The STL provides containers such as vectors, lists, and sets, and a family of fundamental algorithms for searching, sorting, inserting, and deleting.
1. The function _build_ uses the iostream library to read the input one word at a time.
1. The string _buf_ will grow as necessary to handle input words of arbitrary length.
1. The _map_ container overloads subscripting (the [] operator) to behave as a lookup operation.
1. push_back    push_front
1. The C++ version seems especially clear and elegant-the code is compact, the data structure is visible and the algorithm is completely transparent.
1. Sadly, there is a price to pay: this version runs much slower than the original C version, though it is not the slowest.
1. [markov-chain.cpp](cpp/markov-chain.cpp)

### 3.7 Awk and Perl

1. Both the Perl and Awk programs are short compared to the three earlier versions, but they are harder to adapt to handle prefixes that are not exactly two words.
1. The core of the C++ STL implementation (the _add_ and _generate_ functions) is of comparable length and seems clearer.
1. Nevertheless, scripting languages are often a good choice for experimental programming, for making prototypes, and even for production use if run-time is not a major issue.
1. [markov.awk](awk/markov.awk)
1. [markov.pl](perl/markov.pl)

### 3.8 Performance

### 3.9 Lessons

1. Over all that time, however, the basic design has remained the same. The earliest version used the same approach as the ones we have presented here, although it did employ a second hash table to represent individual words.
1. The design of a program is rooted in the layout of its data. The data structures don't define every detail, but they do shape the overall solution.
1. Of course, while the data structures are the same, there is a wide variation in the general appearance of the programs, in the size of the source code, and in performance.
1. Very roughly, higher-level languages give slower programs than lower level ones, although it's unwise to generalize other than qualitatively.
1. Less clear, however, is how to access the loss of control and insight when the pile of system-supplied code gets so big that one no longer knows what's going on underneath.
1. This is a pervasive and growing concern in software: as libraries, interfaces, and tools become more complicated, they become less understood and less controllable.
1. The design and implementation of this program illustrate a number of lessons for larger programs. First is the importance of choosing simple algorithms and data structures, the simplest that will do the job in reasonable time for the expected problem size.
1. Following Brooks's advice, we find it best to start detailed design with data structures, guided by knowledge of what algorithms might be used; with the data structures settled, the code goes together easily.

## Chapter 4: Interfaces

1. Among the issues to be worked out in a design are:
    1. Interfaces: what services and access are provided? The interface is in effect a contract between supplier and customer. The desire is to provide services that are uniform and convenient, with enough functionality to be easy to use but not so much as to become unwieldy.
    1. Information hiding: what information is visible and what is private? An interface must provide straightforward access to the components while hiding details of the implementation so they can be changed without affecting users.
    1. Resource management: who is responsible for managing memory and other limited resources? Here, the main problems are allocating and freeing storage, and managing shared copies of information.
    1. Error handling: who detects errors, who reports them, and how? When an error is detected, what recovery is attempted?

### 4.1 Comma-Separated Values

### 4.2 A Prototype Library

1. It's not usually until you've built and used a version of the program that you understand the issues well enough to get the design right.
1. The prototype issues:
    1. The prototype doesn't handle long input lines or lots of fields. It can give wrong answers or crash because it doesn't even check for overflows, let alone return sensible values in case of errors.
    1. The input is assumed to consist of lines terminated by newlines.
    1. Fields are separated by commas and surrounding quotes are removed. There is no provision for embedded quotes or commas.
    1. The input line is not preserved; it is overwritten by the process of creating fields.
    1. No data is saved from one input line to the next; if something is to be remembered, a copy must be made.
    1. Access to the fields is through a global variable, the field array, which is shared by _csvgetline_ and functions that call it; there is no control over access to the field contents or the pointers. There is also no attempt to prevent access beyond the last field.
    1. The global variables make the design unsuitable for a multi-threaded environment or even for two sequences of interleaved calls.
    1. The caller must open and close files explicitly; _csvgetline_ reads only from open files.
    1. Input and splitting are inextricably linked: each call reads a line and splits it into fields, regardless of whether the application needs that service.
    1. The return value is the number of fields on the line; each line must be split to compute this value,. There is also no way to distinguish errors from end of file.
    1. There is no way to change any of these properties without changing the code.

### 4.3 A Library for Others

1. Interface:
    1. We decided on three basic operations:
        1. char *csvgetline(FILE *): read a new CSV line, return pointer to line, with terminator removed, or NULL if EOF occurred
        1. char *csvfield(int n): return the n-th field of the current line, return NULL if n < 0 or beyond last field
        1. int csvnfield(void): return the number of fields on the current line
1. Information hiding:
    1. Only _csvgetline_ knows about memory management; nothing about the way that it organizes memory is accessible from outside.
    1. We will have to grow memory as longer lines or more fields arrive. Details of how that is done are hidden in the _csv_ functions; no other part of the program knows how this works. Nor does the interface reveal when memory is freed.
    1. If the user calls only _csvgetline_, there's no need to split into fields; lines can be split on demand. Whether field-splitting is eager or lazy or very lazy is another implementation detail hidden from the user.
1. Resource management:
    1. We must decide who is responsible for shared information.
        1. The return value of _csvgetline_ is a pointer to the original input, which will be overwritten when the next line is read.
        1. Fields will be built in a copy of the input line, and _csvfield_ will return a pointer to the field within the copy.
        1. With this arrangement, the user must make another copy if a particular line or field is to be saved or changed, and it is the user's responsibility to release that storage when it is no longer needed.
    1. Who opens and closes the input file?
        1. Whoever opens an input file should do the corresponding close: matching tasks should be done at the same level or place.
        1. We will assume that _csvgetline_ is called with a FILE pointer to an already-open open that the caller will close when processing is complete.
    1. Managing the resources shared or passed across the boundary between a library and its callers is a difficult task, and there are often sound but conflicting reasons to prefer various design choices.
    1. Errors and misunderstandings about the shared responsibilities are a frequent source of bugs.
1. Error handling:
    1. By analogy with ferror, we could add another function _csvgeterror_ to the interface to report the most recent error, but for simplicity we will leave it out of this version.
    1. As a principle, library routines should not just die when an error occurs; error status should be returned to the caller for appropriate action.
    1. Nor should they print messages or pop up dialog boxes, since they may be running in an environment where a message would interfere with something else.
1. Specification:
    1. The choices made above should be collected in one place as a specification of the services that _csvgetline_ provides and how it is to be used.
    1. The best approach is to write the specification early and revise it as we learn from the ongoing implementation.
    1. The more accurate and careful a specification is, the more likely that the resulting program will work well.
1. This specification still leaves open questions. For example, what values should be returned by _csvfield_ and _csvnfield_ if they are called after _csvgetline_ has encountered EOF? How should ill-formed fields be handled?
1. Nailing down all such puzzles is difficult even for a tiny system, and very challenging for a large one, though it is important to try.
1. One often doesn't discover oversights and omissions until implementation is underway.
1. The internal variables that store text and the internal functions like _split_ are declared _static_ so they are visible only within the file that contains them. This is the simplest way to hide information in a C program.

### 4.4 A C++ Implementation

1. [csv.cpp](cpp/csv.cpp)
1. [Exercise-4-5.csv-operator-overload.cpp](cpp/Exercise-4-5.csv-operator-overload.cpp)

### 4.5 Interface Principles

1. To prosper, an interface must be well suited for its task - simple, general, regular, predictable, robust - and it must adapt gracefully as its users and its implementation change.
1. Good interfaces follow a set of principles:
    1. Hide implementation details
        1. There are several terms for this kind of organizing principle; information hiding, encapsulation, abstraction, modularization, and the like all refer to related ideas.
        1. If the header file does not include the actual structure declaration, just the name of the structure, this is sometimes called an **opaque type**, since its properties are not visible and all operations take place through a pointer to whatever real object lurks behind.
        1. Avoid global variables; wherever possible it is better to pass references to all data through function arguments.
        1. We strongly recommend against publicly visible data in all forms;
        1. The predefined I/O streams like _stdin_ and _stdout_ are almost always defined as elements of a global array of **FILE** structures:
            ```C
            extern FILE     __iob[_NFILE];
            #define stdin   (&__iob[0])
            #define stdout  (&__iob[1])
            #define stderr  (&__iob[2])
            ```
        1. This makes the implementation completely visible; it also means that one can't assign to _stdin_, _stdout_ or _stderr, even though they look like variables.
        1. The peculiar name __iob uses the ANSI C convention of two leading underscores for private names that must be visible, which makes the names less likely to conflict with names in a program.
    1. Choose a small orthogonal set of primitives
        1. Having lots of functions may make the library easier to use - whatever one needs is there for the taking. But a large interface is harder to write and maintain, and sheer size may make it hard to learn and use as well.
        1. In the interest of convenience, some interfaces provide multiple ways of doing the same thing, a tendency that should be resisted.
        1. Narrow interfaces are to be preferred to wide ones, at least until one has strong evidence that more functions are needed.
        1. Do one thing, and do it well.
        1. For instance, rather than having _memcpy_ for speed and _memmove_ for safety, it would be better to have one function that was always safe, and fast when it could be.
    1. Don't reach behind the user's back
        1. A library function should not write secret files and variables or change global data, and it should be circumspect about modifying data in its caller.
    1. Do the same thing the same way everywhere

### 4.6 Resource management

1. Free a resource in the same layer that allocated it
    1. One way to control resource allocation and reclamation is to have the same library, package, or interface that allocates a resource be responsible for freeing it.
    1. C++ constructors and destructors
    1. Java _garbage collection_
    1. The existence of automatic garbage collection does **not** mean that there are no memory-management issues in a design.
    1. We still have to determine whether interfaces return references to shared objects or copies of them, nad this affects the entire program.
    1. Nor is garbage collection free - there is overhead to maintain information and to reclaim unused memory, and collection may happen at unpredictable times.
1. To avoid the multi-threaded resource management problems, it is necessary to write code that is _reentrant_, which means that it works regardless of the number of simultaneous executions.
    1. Reentrant code will avoid global variables, static local variables, and any other variable that could be modified while another thread is using it.
    1. Libraries that inadvertently expose variables to sharing destroy the model.
    1. If variables might be shared, they must be protected by some kind of locking mechanism to ensure that only one thread at at time accesses them.
    1. Synchronized methods in Java.

### 4.7 Abort, Retry, Fail?

1. Detect errors at a low level, handle them at a high level
    1. In most cases, the caller should determine how to handle an error, not the callee. Library routines can help in this by failing gracefully.
    1. That reasoning led us to return NULL for a non-existent field rather than aborting. Similarly, _csvgetline_ returns NULL no matter how many times it is called after the first end of file.
1. Use exceptions only for exceptional situations
    1. Exceptions should not be used for handling expected return values. Reading from a file will eventually produce an end of file; this should be handled with a return value, not by an exception.
    1. Exceptions are often overused, because they distort the flow of control, they can lead to convoluted constructions that are prone to bugs.
    1. Exceptions are best reserved for truly unexpected events, such as file systems filling up or floating-point errors.

### 4.8 User Interfaces

1. A diagnostic should not say:
    ```text
    estrdup failed
    ```
1. when it could say:
    ```text
    markov: estrdup("Derrida") failed: Memory limit reached
    ```
1. Programs should display information about proper usage when an error is made, as shown in functions like:
    ```c
    /* usage: print usage message and exit */
    void usage(void)
    {
        fprintf(stderr, "usage: %s [-d] [-n nwords] [-s seed] [files ...]\n", progname());
        exit(2);
    }
    ```

## Chapter 5: Debugging

1. Why should software be so hard?
    1. One reason is the the complexity of a program is related to the number of ways that its components can interact, and software is full of components and interactions.
1. A major force in the evolution of programming languages has been the attempt to prevent bugs through language features.
1. Programmers should know the potentially risky bits of their languages and take extra care when using them. They should also enable all compiler checks and heed the warnings.
1. Each language feature that prevents some problem has a cost of its own. If a higher-level language makes the simple bugs disappear automatically, the price is that it makes it easier to create higher-level bugs.

### 5.1 Debuggers

### 5.2 Good Clues, Easy Bugs

1. Look for familiar patterns
    1. Uninitialized variables usually give a garbage values. Memory returned by allocators like _malloc_, _realloc_, and _new_ is likely to be garbage too; be sure to initialize it.
1. Examine the most recent change
1. Don't make the same mistake twice
    1. Even when code is so simple you could write it in your sleep, don't fall asleep while writing it.
1. Debug it now, not later
1. Get a stack trace
1. Read before typing
    1. Resist the urge to start typing; thinking is a worthwhile alternative.
1. Explain your code to someone else

### 5.3 No Clues, Hard Bugs

1. Make the bug reproducible
1. Divide and conquer
    1. Proceed by binary search. Throw away half the input or the code to identify which parts have the bug.
1. Study the numerology of failures
1. Display output to localize your search
1. Write self-checking code
1. Write a log file
1. Draw a picture
1. Use tools
1. Keep records

### 5.4 Last Resorts

1. debugger

### 5.5 Non-reproducible Bugs

1. Check whether all variables have been initialized. Local variables of functions and memory obtained from allocators are the most likely culprits in C and C++
1. If the bug changes behavior or even disappears when debugging code is added, it may be a memory allocation error
1. Returning the address of a local variable is a recipe for delayed disaster
1. You can write your own allocator that does some of its own consistency checking or logs all calls for separate analysis. An allocator that doesn't have to run fast is easy to write, so this strategy is feasible when the situation is dire.

### 5.6 Debugging Tools

1. [strings.c](strings.c)
1. [Exercise-5-2.strings-length-option](Exercise-5-2.strings-length-option.c)
1. [vis](vis.c)

### 5.7 Other People's Bugs

1. Before debugging others' code, you must first acquire some understanding of how the program is organized and how the original programmers thought and wrote.
1. Helpful tools: Text-search, Graph of function calls, Revision history and Debugger

### 5.8 Summary

## Chapter 6: Testing

1. One way to write bug-free code is to generate it by a program. A common case occurs when a program can be generated from a specification in some specialized language

### 6.1 Test as You Write the Code

1. Test code at its boundaries - boundary condition testing
1. Test pre- and post-conditions
    1. Making sure that input values are within range is a common example of testing a pre-condition
1. Use assertions
    1. Assertions are particularly helpful for validating properties of interfaces because they draw attention to inconsistencies between caller and callee and my even indicate who's at fault
1. Program defensively
    1. _defensive programming_ is a useful technique to make sure that a program protects itself against incorrect use or illegal data
1. Check error returns

### 6.2 Systematic Testing

1. Test incrementally
    1. Write part of a program, test it, add some more code, test that, and so on.
1. Test simple parts first
    1. Test should focus first on the simplest and most commonly executed features of a program
1. Know what output to expect
    1. To test a numerical program, generate test cases that explore the edges of the algorithm, trivial cases as well as hard ones.
    1. If the program has an inverse, check that its application recovers the input. Encryption and decryption are inverse.
1. Verify conservation properties
1. Compare independent implementations
    1. Independent implementations of a library or program should produce the same answers
    1. Sometimes an answer can be computed in two different ways, or you might be able to write a trivial version of a program to use as a slow but independent comparison
    1. If two unrelated programs get the same answers, there is a good chance that they are correct; if not, at least one is wrong
1. Measure test coverage
1. [freq](freq.c)
1. [Exercise 6.2](freq-numbers.c)

### 6.3 Test Automation

1. Automate regression testing
    1. If an erroneous answer ever sneaks into a regression tet, it's very hard to detect and everything depends on it will be wrong thereafter
    1. It's good practice to check the regression test itself periodically to make sure it is still valid
    1. [test-ka](test-ka.sh)
1. Create self-contained tests

### 6.4 Test Scaffolds

1. [memset-test](memset-test.c)

### 6.5 Stress Tests

1. Buffer overflow
    1. A few standard library functions are vulnerable to some security attacks using big or illegal inputs that overwrite precious data
    1. For instance, standard library function _gets_ provides no way to limit the size of an input line, so it should **never** be used; always use _fgets(buf, sizeof(buf), stdin)_ instead
    1. scanf("%s", buf) doesn't limit the length of an input line either, use scanf("%20s", buf) instead
1. Any routine that might receive values from outside the program, directly or indirectly, should validate its input values before using them
1. Good tedt cases can often be used on a variety of programs. For example, any program that reads files should be tested on an empty file. Any program that reads text should be tested on binary files. Any program that reads text lines should be tested on huge lines and empty lines and input with no newlines at all.

### 6.6 Tips for Testing

1. To exercise the array bounds checks, temporarily make the array sizes very small, which is easier than creating large test cases
1. Make the hash function return a constant, so every element gets installed in the same hash bucket
1. Write a version of your storage allocator that intentionally fails early, to test your code for recovering from out-of-memory errors
1. Initialize arrays and variables with some distinctive value, rather than the usual default of zero; then if you access out of bounds or pick up an uninitialized variable, you are more likely to notice it. The constant 0xDEADBEEF is easy to recognize in a debugger

### 6.7 Who Does the Testing

1. Boundary conditions are a good place to begin black box testing; high-volume, perverse, and illegal inputs are good follow-ons

### 6.8 Testing the Markov Program

### 6.9 Summary

1. The single most important rule of testing is to _do it_

## Chapter 7: Performance

1. A fast program that gets the wrong answer doesn't save any time.
1. The first principle of optimization is _don't_

### 7.1 A Bottleneck

1. When solving problems, it's important to ask the right question
1. Trading space for time, precomputation
1. Use profiling and other techniques to study the behavior and learn where the problem really lay
1. Make sure solving the right problem, examining the overall program rather than just focusing on some point
1. Using a better algorithm solve the problem and check it's really faster, don't over-engineer

### 7.2 Timing and Profiling

1. Automate timing measurements
    1. Unix command _time_
1. Use a profiler
    1. A _profile_ is a measurement of where a program spends its time
    1. Profiling is an effective tool for finding _hot spots_ in a program, the functions or sections of code that consume most of the computing time
    1. Don Knuth: "Less than 4 percent of a program generally accounts for more than half of its running time"
1. Concentrate on the hot spots
1. Draw a picture

### 7.3 Strategies for Speed

1. Before changing a program to make it faster, be certain that it really is too slow, and use timing tools and profilers to discover where the time is going
1. Use a better algorithm or data structure
1. Enable compiler optimizations
1. Tune the code
    1. for example, something do not need to recompute inner the loop if it is a fixed value; like array[c] and strlen(s)
1. Don't optimize what doesn't matter
    1. Make sure the code you're optimizing is where time is really spent

### 7.4 Tuning the Code

1. Compilers will do some optimization for you, and in fact you may impede their efforts by complicating the program. Whatever you try, _measure_ its effct to make sure it helps
1. Collect common subexpressions
    1. If an expensive computation appears multiple times, do it in only one place and remember the result
1. Replace expensive operations by cheap ones
1. Unroll or eliminate loops

    ```c
    for (i = 0; i < 3*n; i++)
        a[i] = b[i] + c[i];
    ```

    becomes

    ```c
    for (i = 0; i < 3*n; i += 3)
    {
        a[i+0] = b[i+0] + c[i+0];
        a[i+1] = b[i+1] + c[i+1];
        a[i+2] = b[i+2] + c[i+2];
    }
    ```

    1. Note that this works only if the length is a multiple of the step size
    1. Otherwise additional code is needed to fix up the ends, which is a place for mistakes to creep in and for some of the efficiency to be lost again

1. Cache frequently-used values
1. Write a special-purpose allocator
    1. The special-purpose allocator can fetch a big array of items and then hands them out one at a time as needed, and freed items are placed back in a _free list_ so they can be reused quickly
1. Buffer input and output
1. Handle special cases separately
1. Precompute results
    1. For example, the **ctype** functions like **isdigit** are almost always implemented by indexing into a table of bit flags rather than by evaluating a sequence of tests
1. Use approximate values
    1. single-precision floating-point arithmetic is often faster than double-precision, so use _float_ instead of _double_ to save time if _accuracy_ isn't an issue
    1. The use of integer sin and cos routines is another example of using approximate values
1. Rewrite in a lower-level language

### 7.5 Space Efficiency

1. Save space by using the smallest possible data type
1. Don't store what you can easily recompute
    1. Store the common value or values implicitly or in a compact form, and spend more time and space on the remaining values. If the most common values are really common, this is a win

### 7.6 Estimation

### 7.7 Summary

## Chapter 8: Portability

## Chapter 9: Notation

### 9.1 Formatting Data

1. _Little language_ are specialized notations for narrow domains. They not only provide a good interface but also help organize the program that implements them. The _printf_ control sequences are a good example
1. ANSI C says that we can always store at least 8 bits in a _char_, 16 bits in a _short_, and 32 bits in a _long_
1. The inherent repetitiveness of the code is a clue that notation can help
1. [pack.c](pack.c)

### 9.2 Regular Expressions

1. [my-grep.c](my-grep.c)

### 9.3 Programmable Tools

### 9.4 Interpreters, Compilers, and Virtual Machines

1. [compiler-v1.c](compiler-v1.c)
1. [compiler-v2.c](compiler-v2.c)
