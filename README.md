
The listed programs were used to generate all valid Icelandic
[kennitala](https://en.wikipedia.org/wiki/Kennitala), then create a DFA that
recognizes them. It was huge, containing 13.6 million states. This DFA was then minimized with
[this](http://www.cs.tut.fi/~ava/DFA_minimizer.cc) program. Surprisingly, you only need [132 states](https://github.com/SuprDewd/kennitala_regex/blob/master/min.txt) to match Icelandic kennitala!

The [states](https://github.com/SuprDewd/states) program was then used to generate [this regex](https://x.algo.is/eats) (warning: large file) for matching Icelandic kennitala. Unfortunately it's huge. Next step is to make it smaller...
