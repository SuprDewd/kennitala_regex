
The listed programs were used to generate all valid Icelandic
[kennitala](https://en.wikipedia.org/wiki/Kennitala), then create a DFA that
recognizes them. This DFA was then minimized with
[this](http://www.cs.tut.fi/~ava/DFA_minimizer.cc) program.

The [states](https://github.com/SuprDewd/states) program was then used to generate [this regex](https://x.algo.is/eats) (warning: large file) for matching Icelandic kennitala's. Unfortunately it's huge. Next step is to make it smaller...
