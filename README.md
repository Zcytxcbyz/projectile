# Projectile Motion Calculator with Air Drag

A C program that calculates the landing point and flight time of a projectile, accounting for air resistance. Built with CMake for cross-platform compatibility.

## Features

- Calculates both drag and no-drag (k=0) scenarios
- Validates physical input parameters
- Implements Newton's method for numerical solution
- Command-line interface for easy integration
- CMake build system support

## Prerequisites

- C compiler (GCC, Clang, or MSVC)
- CMake (version 3.10 or higher)
- Math library (included automatically)

## Installation

```bash
# Clone the repository
git clone https://github.com/zcytxcbyz/projectile.git
cd projectile

# Configure and build
mkdir build
cd build
cmake ..
make
```

## Usage

```bash
./projectile <v0> <theta_deg> <m> <g> <k>
```

### Arguments:
| Parameter | Description                     | Units   | Valid Range        |
|-----------|---------------------------------|---------|-------------------|
| v0        | Initial velocity                | m/s     | > 0               |
| theta_deg | Launch angle                    | degrees | 0 ≤ θ ≤ 90        |
| m         | Mass of projectile              | kg      | > 0               |
| g         | Gravitational acceleration      | m/s²    | > 0               |
| k         | Air drag coefficient (0 for none)| kg/s    | ≥ 0               |

### Example:
```bash
# With air drag (k=0.1)
./projectile 20 45 1 9.8 0.1

# Without air drag (k=0)
./projectile 20 45 1 9.8 0
```

## Sample Output

```
Input Parameters:
  v0 = 20.00 m/s
  θ  = 45.00 deg
  m  = 1.00 kg
  g  = 9.80 m/s²
  k  = 0.10 kg/s
Results:
  Distance = 35.35 m
  Time     = 2.88 s
```

## Mathematical Model

### With Air Resistance (k > 0):
- Horizontal motion: `v_x(t) = v_x0 * exp(-k/m * t)`
- Vertical motion: `v_y(t) = (v_y0 + mg/k)exp(-k/m * t) - mg/k`
- Solved numerically using Newton's method

### Without Air Resistance (k = 0):
- Closed-form solutions:
  - `t_f = 2v_y0/g`
  - `x_f = v_x0 * t_f`

## License

MIT License. See LICENSE file for details.

## Contributing

1. Fork the repository
2. Create a feature branch
3. Submit a pull request

Bug reports and feature requests are welcome via GitHub issues.