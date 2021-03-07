# Motor-encoder-simulator
Using Arduino Pro-Mini, the motor-encoder simulator is constructed. With the inverted input PWM pulses filtered by a LPF, a DC voltage is generated.
This DC voltage is hence inversely proportional to PWM duty cycle. The code measures this voltage and re-generate a pair of two-phase encoder signals with variable frequency.
