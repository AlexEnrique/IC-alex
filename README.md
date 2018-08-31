# Visualization for the Isotropic 2D Ising Model.
<h2> Running the visualization </h2>

- Go to [this link](https://alexenrique.github.io/IC-alex/JS-2dIsing/).

**Or**

1. Download all the files inside the folder *JS-2dIsing*.
2. Open "index.html" using an internet browser.

<hr />

- Open the console of your browser to see messages from the program.
- You can change the JS code <code>sketch.js</code> and <code>func.js</code> and refresh the index.html page opened, if you download the files.

<h2> Understanding the simulation </h2>

When you open the simulation, it will look like this:

<img src="https://github.com/AlexEnrique/IC-alex/blob/IsingJS-v1.2/IsingVS.png?raw=true" alt="2D-Ising" title="2D Ising Simulation" class="center" />

From the left to the right, there are the <code>temperature slider</code> and the <code>temperature box</code> and the buttons <code>Set temperature</code> and <code>Phase transition</code>. On the middle part, there existis optins for the <code>Spins arrangment</code> and the <code>Magnetic Field</code>. At the righest area, lives four button to <code>start</code> and <code>stop</code> the simulation, to <code>restart</code> a simulation stopped and to <code>reset</code> the entire lattice.

* The <code>temperature slider</code> enables you to change the temperature in some range. 
* The <code>temperature box</code> enables you to change the temperature to what value you want.
* The button <code>Set temperature</code> changes to the a new temperature, the last one writted in the box or in the slider.
* The button <code>Phase transition</code> changes the temperature to the phase transition temperature. It will be displayed at the browser console.
  + Keep in mind that the Boltzmann constant and the coupling term of the Hamiltonian are set to 1.

+ The options of <code>Spins arrangment</code> are:
  - Random,
  - Paralel,
  - Anti-paralel. 
It can be changed any momento, during or after the simulation have been started.
+ The options of <code>Magnetic Field</code> are:
  - Off,
  - Very weak,
  - Weak,
  - Regular,
  - Strong,
  - Very strong.
The values used for the magnetic field can be view by typing **B** into your browser console (see next section).

* The actions buttons <code>start</code>, <code>stop</code>, <code>restart</code> and <code>reset</code> were explained above. 
  
<h2>Changing and seeing some specific values</h2>
Using the browser console (usually <code>ctrl+shift+J</code>), you can change and see some values more precisely, for example, the magnetic field.
  
* Typing **B** into the console, you can see the exacly value of the magnetic field. 
* The value of **B** can be changed doing something like <code>B = float_number</code>.
* The temperatura and the phase transition temperature can be visualized by entering <code>temperature</code> and <code>phaseTransitionTemp</code>, respectively. 
* The mean energy and the mean absolute magnetization can be visualized by typing **E** and **Mabs** into the console.
 
<hr />
<h3>Thanks</h3>

This simulation code was based on the [coding challenge #85](http://thecodingtrain.com/CodingChallenges/085-the-game-of-life.html), by [Daniel Shiffman](https://github.com/shiffman).

I hope you enjoy the visualization. 
<br />
\- Alex Enrique Crispim.
