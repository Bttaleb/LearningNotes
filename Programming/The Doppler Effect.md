[![The Doppler effect: From highly ridiculed to absolutely indispensable, Part  1](https://www.microcontrollertips.com/wp-content/uploads/2022/04/WTWH_Doppler_Pt1_Fig1.png)![The Doppler effect: From highly ridiculed to absolutely indispensable, Part  1](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcSZ4tF9JMr92ij8WXBPwR6a_RX8AJ_b_qC5w5dROMTpOg&s=10)](https://www.google.com/url?sa=t&source=web&rct=j&url=https%3A%2F%2Fwww.microcontrollertips.com%2Fthe-doppler-effect-from-highly-ridiculed-to-absolutely-indispensable-part-1%2F&ved=0CBcQjRxqFwoTCJi1yaf2lpcDFQAAAAAdAAAAABA4&opi=89978449)
### What Is It?
- The change in a wave's frequency or wavelength that occurs when the source of the wave and the observer are moving relative to each other
### 1. Generating Wave Fronts (The Source)
- NOT a continuous wave
	- Emission Trigger: Every T<sub>s</sub> seconds (T<sub>s</sub> = 1/f<sub>s</sub>), simulation records the current (x<sub>s</sub>, y<sub>s</sub>) position of the source and resets the timer
	- Wave Expansion: For each generated wave, its radius *R* at any elapsed time *t* since its creation is calculated by R(t) = v * t, where v = speed of sound

### 2. Moving the Entities
- In every frame (updates at time step Δt), position of source and observer are updated based on their velocities
	- Source Position: x<sub>s</sub> = x<sub>s</sub> + (v<sub>s,x</sub> * Δt)
	- Observer Position: x<sub>o</sub> = x<sub>o</sub> + (v<sub>o,x</sub> * Δt)
### 3. Detecting Perceived Frequency (Observer)
- To simulate the observer "hearing", we calculate when a wave front's expanding radius intersects with the observer's moving position
- Wave fronts are emitted from the center (x<sub>c</sub>, y<sub>c</sub>) reaches the observer (x<sub>o</sub>, y<sub>o</sub>) when distance between them **equals** the wave's radius
	- d = √(x<sub>o</sub> - x<sub>c</sub>)^2 + (y<sub>o</sub> - y<sub>c</sub>)^2
- Detection Event: Code will check every frame if d (distance) <= R(t). Whenever the condition transitions from false to true, the simulation registers a "hit" (peak of wave reached the observer)
- Observed Frequency (f<sub>o</sub>): Our simulation tracks the time interval between consecutive hits (ΔT<sub>obs</sub>) -> Perceived frequency is then calculated dynamically in the code as f<sub>o</sub> = 1/(ΔT<sub>obs</sub>)

### Vector-Based Algebraic Formula
- Calculating the exact frequency WITHOUT counting wave intersections can be done using the **vector Doppler formula**: f<sub>o</sub> = f<sub>s</sub>((v-v<sub>o</sub>⋅ r)/(v-v<sub>s</sub> ⋅ r))
- v<sub>s</sub> and v<sub>o</sub> : velocity vectors of *source* and *observer*
- r : *unit vector* pointing directly from the *source* to the *observer*
	- r = ( pos<sub>o</sub> - pos<sub>s</sub>) / ( |pos<sub>o</sub> - pos<sub>s</sub>| )