## Week 02

### Copy paste the latest code into the code section here: https://app.cirkitdesigner.com/project/934460b0-a08c-455a-97dc-35d2d97a4052

We have implemented a template code base for the spinning motor mechanism.
The template comprises of pin connections, calibration constants and test functions to verify the motor and encoder are working properly.
In the meantime, we can test the code through a tinkercad simulation.
Once Harry and Raki have wired the physical components, Denny, Harrison and Alex can update the constants (pin numbers, COUNTS_PER_REV) to match the actual hardware.
COUNTS_PER_REV is measured by hand-rotating the shaft and counting.
The DRV8874's current limit (VREF) needs to be changed so that the motor doesn't stall but has enough to turn the flywheel.
