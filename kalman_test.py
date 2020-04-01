err_measure = 1.0   # Measurement Uncertainty - How much do we expect to our measurement vary
err_estimate = 1.0  # Estimation Uncertainty - Can be initilized with the same value as e_mea since the kalman filter will adjust its value.
pro_variance = 0.01 # Process Variance - usually a small number between 0.001 and 1 - how fast your measurement moves. 
                    # Recommended 0.01. Should be tunned to your needs.

kalman_gain = 0.0
current_estimate = 0.0
last_estimate = 0.0

sensorVal = 50

kalman_gain = err_estimate/(err_estimate + err_measure)
current_estimate = last_estimate + kalman_gain * (sensorVal - last_estimate)
err_estimate =  (1.0 - kalman_gain) * err_estimate + abs(last_estimate-current_estimate) * pro_variance
last_estimate = current_estimate

print(current_estimate)
