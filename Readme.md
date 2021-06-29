# Laplace Solver
We solve 
$$div(\theta)=0$$

Using finite differencing
$$\Delta \theta = \Delta t \, \alpha \ \dfrac{\theta_{(i+1)j}-2\, \theta_{ij} +\theta_{(i-1)j}}{dx^{2}} + \dfrac{\theta_{i(j+1)}-2\, \theta_{ij} +\theta_{i(j-1)}}{dy^{2}}$$

# Abort criterion
The solver is supposed to achieve a steady state solution. Hence we will check for the change in the increments, wether it reaches a steady state.
Further, the time step size is reduced to half, when this trend is positive.