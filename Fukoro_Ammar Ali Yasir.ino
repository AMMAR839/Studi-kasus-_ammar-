import numpy as np
import matplotlib.pyplot as plt

# Time step for simulation (interval between updates)
dt = 0.1

# State transition matrix F
F = np.array([[1, 0, dt, 0],       # x position is updated by adding velocity * dt
              [0, 1, 0, dt],       # y position is updated by adding velocity * dt
              [0, 0, 1, 0],        # x velocity is carried over (remains the same)
              [0, 0, 0, 1]],       # y velocity is carried over (remains the same)
             dtype=np.float64)

# Control matrix B
B = np.array([[0.5 * dt**2, 0],     # x position affected by acceleration * 0.5 * dt^2
              [0, 0.5 * dt**2],     # y position affected by acceleration * 0.5 * dt^2
              [dt, 0],              # x velocity affected by acceleration * dt
              [0, dt]],             # y velocity affected by acceleration * dt
             dtype=np.float64)

# Measurement matrix H
H = np.eye(4, dtype=np.float64)

# Process covariance matrix Q
Q = np.eye(4, dtype=np.float64) * 0.1

# Measurement noise covariance matrix R
R = np.eye(4, dtype=np.float64) * 5

# Initial state of the aircraft [x, y, vx, vy]
x_target = np.array([0, 1000, 20, 5], dtype=np.float64).reshape(-1, 1)

# Initial state covariance
P = np.eye(4, dtype=np.float64) * 500

# Initial estimate of target acceleration
u_target = np.array([0.2, 0.1], dtype=np.float64).reshape(-1, 1)

# Initialize arrays for storing positions and Kalman Gain
target_positions = []
missile_positions = []
predicted_positions = []
kalman_gains = []
corrections = []

# Missile state [x, y, vx, vy]
x_missile = np.array([0, 0, 10, 10], dtype=np.float64).reshape(-1, 1)
missile_speed = 80  # constant missile speed

# Function to get new target state
def update_target_state(x_target, u_target):
    u_target += np.random.randn(2, 1) * 0.05
    x_target = F @ x_target + B @ u_target
    return x_target, u_target

# Initialize impact detection
impact_detected = False
impact_index = -1

# Kalman filter loop
for i in range(300):
    # Simulate target motion
    x_target, u_target = update_target_state(x_target, u_target)

    # Predict step
    x_pred = F @ x_target + B @ u_target
    P_pred = F @ P @ F.T + Q

    # Measurement (with noise)
    z = x_target + np.random.randn(4, 1) * 10

    # Kalman gain
    K = P_pred @ H.T @ np.linalg.inv(H @ P_pred @ H.T + R)

    # Update step
    x_est = x_pred + K @ (z - H @ x_pred)
    P = (np.eye(4) - K @ H) @ P_pred

    # Store positions and Kalman Gain for plotting
    target_positions.append(x_target[:2].flatten())
    predicted_positions.append(x_pred[:2].flatten())
    missile_positions.append(x_missile[:2].flatten())
    kalman_gains.append(np.linalg.norm(K))  # Store norm of Kalman Gain for simplicity
    corrections.append((z - H @ x_pred).flatten())

    # Missile control (simple pursuit model)
    missile_direction = x_est[:2] - x_missile[:2]
    missile_direction = missile_direction / np.linalg.norm(missile_direction)
    x_missile[:2] += missile_direction * missile_speed * dt

    # Check for impact
    distance_to_target = np.linalg.norm(x_missile[:2] - x_est[:2])
    if distance_to_target < 5.0:
        impact_detected = True
        impact_index = i
        break

# Convert to arrays for plotting
target_positions = np.array(target_positions)
missile_positions = np.array(missile_positions)
predicted_positions = np.array(predicted_positions)
kalman_gains = np.array(kalman_gains)
corrections = np.array(corrections)

# Plotting the results
plt.figure(figsize=(18, 6))

# Plot target and missile paths
plt.subplot(1, 3, 1)
plt.plot(target_positions[:, 0], target_positions[:, 1], label="Jalur Target", color='blue')
plt.plot(missile_positions[:, 0], missile_positions[:, 1], label="Jalur Rudal", color='red')
if impact_detected:
    plt.plot(missile_positions[impact_index, 0], missile_positions[impact_index, 1], 'go', label="Titik Impact")
    plt.plot(target_positions[impact_index, 0], target_positions[impact_index, 1], 'bo', label="Posisi Target Saat Impact")
plt.xlabel("Posisi X")
plt.ylabel("Posisi Y")
plt.title("Jalur Target dan Rudal")
plt.legend()
plt.grid(True)

# Plot predicted positions
plt.subplot(1, 3, 2)
plt.plot(target_positions[:, 0], target_positions[:, 1], label="Posisi Target Sebenarnya", color='blue')
plt.plot(predicted_positions[:, 0], predicted_positions[:, 1], label="Posisi Prediksi Kalman", color='green', linestyle='--')
if impact_detected:
    plt.axvline(x=missile_positions[impact_index, 0], color='orange', linestyle=':', label="Garis Impact")
plt.xlabel("Posisi X")
plt.ylabel("Posisi Y")
plt.title("Posisi Prediksi Kalman")
plt.legend()
plt.grid(True)

# Plot Kalman Gain dan koreksi
plt.subplot(1, 3, 3)
plt.plot(kalman_gains, label="Norm Kalman Gain", color='purple')
plt.xlabel("Langkah Waktu")
plt.ylabel("Norm Kalman Gain")
plt.title("Kalman Gain dan Koreksi")
plt.legend()
plt.grid(True)

plt.tight_layout()
plt.show()

# Print impact notification
if impact_detected:
    print(f"Rudal mengenai pesawat pada {impact_index * dt:.1f} detik.")
    print(f"Posisi Rudal saat impact ({missile_positions[impact_index, 0]:.2f}, {missile_positions[impact_index, 1]:.2f})")
    print(f"Posisi Pesawat saat impact ({target_positions[impact_index, 0]:.2f}, {target_positions[impact_index, 1]:.2f})")
else:
    print("Rudal tidak mengenai pesawat dalam waktu simulasi.")

