[Docs Home](.)

# Quick Tour

First, either [build HMSL](build.md) or download a [precompiled release](https://github.com/philburk/hmsl/releases).

1. Double click JuceHMSL.app
1. Hit 'y' key to initialize HMSL.
1. Launch a synthesizer program like [Simple Synth](http://notahat.com/simplesynth/) and select "HMSL" as the MIDI source.

To test MIDI output, enter:

    midi.seqout

You should hear a few notes play. Now enter:

    shep
    
The Shape Editor window should appear and you should hear a repeated melody. Click the "Draw" option.
Draw on the graph to extend the melody.
Close the graphics window to stop the editor.

HMSL include a text based score entry system. Enter:

    score{
    playnow  c4  a  g  e

To play notes using a Forth DO LOOP enter:

    playnow 4 0 do  1/4 c4  1/8 a g  1/4 e loop

HMSL includes [several](https://github.com/philburk/hmsl/tree/master/hmsl/pieces) old algorithmic compositions. Most of them are designed to work with a General MIDI Synthesizer.
[XFORMS](https://github.com/philburk/hmsl/blob/master/hmsl/pieces/xforms.fth) is a piece that copies a theme and then ornaments it. 
To compile and run it, enter:

    include pieces/xforms.fth
    xforms

Click up arrow in "Select Shape" widget to see "sh-devel". You can watch the theme be copied and modified.

Read more tutorials and docs at <http://www.softsynth.com/hmsl/>
