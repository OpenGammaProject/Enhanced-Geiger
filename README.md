# Enhanced Geiger

Failed project of mine to build an improved version of the [Better Geiger](https://www.bettergeiger.com/). Some parts were really promising, but I've come to some big hurdles and figured I might as well dump everything on here instead of letting it rot on my PC.

## What worked?

- Much smaller overall size (bare PCB only, don't know about the case, but it's easily optimized)
- 1200 mAh rechargable LiPo battery with a MUCH longer battery life (around 100 hours) EVEN WITH A RASPBERRY PI PICO. I'd call that a win. The Pico has to be always on for the interrupts and it's really not famous for its low-power states.
- Much larger plastic scintillator (!)
- Larger OLED display (0.96 inch vs. 0.75 inch)
- Easily possible to add a vibration motor
- Possibly also the option to (very roughly) gauge the energy of a photon
- Otherwise pretty similar features

## What didn't work?

- Getting signal from the plastic scintillator. I could only get very high energies and count rates to show up. Wasn't able to detect anything below say 600 keV. Not sure what's up there, would have to heavily investigate this, but with the other issues, it's really not worth it for me.
- It would be more expensive of course. At least somewhere double the price, depending on your profit margin obviously. But that wasn't actually a target for me anyways, so it's more neutral. And also, I'm based in the EU, so everything is much more expensive anyways. If you'd manufacture everything in the US or China it's probably not that big of a deal.
- Mounting the SiPM on the scintillator and that whole assembly onto the PCB so that it doesn't fall apart immediately is also a big problem.
- Finding an off-the-shelf case that could fit a device like this without needing heavy work/machining is practically impossible. A custom-built case would be needed, but that's way to expensive considering there is not much commercial value in this project. Maybe you could 3D-print something, but I don't have a printer lol.

## Misc Photos

Here are two photos of what the first iteration of the board with the display looked like (latest iteration is the second one) just to demonstrate the software. The second iteration board is a lot more sound on most of the connections and board layout.

<p align="center">
	<img src="Docs/demo1.jpg" height="500px">
	<img src="Docs/demo2.jpg" height="500px">
</p>

---

Have fun with the files. Do whatever the hell you want with it in accordance to the license.

[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/J3J61GLR3G)
