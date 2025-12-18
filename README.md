[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=21666676)
# ELEC2645 Unit 2 Personal Project 
James Clothier: tztb2418, 201911998

this is a waveform animator to be used as an eductional tool to teach people the effect of changing amplitude and frequency on different waveforms. at the moment only the sine is finished and the saw displays a wave but can not be changed by amplitude and frquency setting. please input an "m" after the welcome screen is shown for the main menu and then input either "sine","saw","inverse saw","square","triangle" or "exit". after selecting "sine" youl be asked to input amplitude and frequency, please do so according to the prompt. A corresponding sine wave will be animated with your settings. Please make sure the terminal window is wide enough to see the full output.

# Run code

You can build the code with 
`gcc main.c -o main.out -lm` (the `-lm` is required to link the math library). You can also use `make -B` to force a rebuild using the provided `Makefile`.

Then run the code with `./main.out`

