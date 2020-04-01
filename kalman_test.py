err_measure = 1.0
err_estimate = 1.0
pro_variance = 0.01

kalman_gain = 0.0
current_estimate = 0.0
last_estimate = 0.0

sensorVal = 50

kalman_gain = err_estimate/(err_estimate + err_measure)
current_estimate = last_estimate + kalman_gain * (sensorVal - last_estimate)
err_estimate =  (1.0 - kalman_gain)*err_estimate + abs(last_estimate-current_estimate)*pro_variance
last_estimate = current_estimate

print(current_estimate)

sensorVal = 52

kalman_gain = err_estimate/(err_estimate + err_measure)
current_estimate = last_estimate + kalman_gain * (sensorVal - last_estimate)
err_estimate =  (1.0 - kalman_gain)*err_estimate + abs(last_estimate-current_estimate)*pro_variance
last_estimate = current_estimate

print(current_estimate)

sensorVal = 51

kalman_gain = err_estimate/(err_estimate + err_measure)
current_estimate = last_estimate + kalman_gain * (sensorVal - last_estimate)
err_estimate =  (1.0 - kalman_gain)*err_estimate + abs(last_estimate-current_estimate)*pro_variance
last_estimate = current_estimate

print(current_estimate)

sensorVal = 48

kalman_gain = err_estimate/(err_estimate + err_measure)
current_estimate = last_estimate + kalman_gain * (sensorVal - last_estimate)
err_estimate =  (1.0 - kalman_gain)*err_estimate + abs(last_estimate-current_estimate)*pro_variance
last_estimate = current_estimate

print(current_estimate)