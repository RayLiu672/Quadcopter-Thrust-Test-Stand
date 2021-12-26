# --------Clarification needed on final time (min/max) for rpm and force ---------------------------------------------
import pandas as pd
import numpy as np

# RPM Data
rpm_file_data = pd.read_csv(r'C:\Users\rayli\Downloads\Test_RPM_CSV.csv', header=0)
# Individual rpm_file_data columns(time, rpm)
time_rpm = pd.DataFrame(rpm_file_data, columns=['Time (msec)'])
rpm_data = pd.DataFrame(rpm_file_data, columns=['RPM'])

# Force Data(all columns)
force_file_data = pd.read_csv(r'C:\Users\rayli\Downloads\Test_Force_Input.csv', header=0)
# Individual force_file_data columns(Time, Input, Force)
time_force = pd.DataFrame(force_file_data, columns=['Time (msec)'])
input_data = pd.DataFrame(force_file_data, columns=['Input'])
force_data = pd.DataFrame(force_file_data, columns=['Force (lbf)'])

# Shifted the time to start at minimum for rpm/force
# --------------------------------------------------consider absolute value? -------------------------------------------
shifted_time_rpm = time_rpm - time_force['Time (msec)'].min()
shifted_time_force = time_force - time_rpm['Time (msec)'].min()

# Initial/Final Time. Used to create the time vector
initial_time = max(shifted_time_rpm['Time (msec)'].min(), shifted_time_force['Time (msec)'].min())
# Select minimum bc there is data available for both rpm and force ----- why subtract initial time ---------------------
final_time = (min(shifted_time_rpm['Time (msec)'].max(), shifted_time_force['Time (msec)'].max())) - initial_time
CONST_DT = 1/50

# Time vector for interpolation(start from 0/initial_time to final_time+DT at intervals of CONST_DT)
#  -------------------------------why add CONST_DT to final_time-------------------------------------------------------
time_vec = np.arange(0, final_time+CONST_DT, CONST_DT)

# Adds the column rpm_data to shifted_time_rpm
shifted_time_rpm['rpm'] = rpm_data
# Initial to Final value of shifted_time_rpm, at intervals of time_vec
df_rpm = pd.DataFrame(shifted_time_rpm)
df_rpm = df_rpm.set_index('Time (msec)')
df_rpm_time_index = pd.DataFrame(df_rpm, time_vec)
df_rpm_time_index.index.name = ('Time (msec)')
# Interpolate then exclude values greater than final time from result
df_interpolated_rpm = df_rpm_time_index.interpolate()
df_interpolated_rpm = df_interpolated_rpm.reset_index()

# Adds the column force_data to shifted_time_force
shifted_time_force['Force(lbf)'] = force_data
# Initial to Final value of shifted_time_force, at intervals of time_vec
shifted_time_force['Input'] = input_data
# Convert shifted_time_force to DataFrame
df_force = pd.DataFrame(shifted_time_force)
# Set Index to be Time
df_force = df_force.set_index('Time (msec)')
# Set df_force to dataframe with intervals of time_vec
df_force_time_index = pd.DataFrame(df_force, time_vec)
df_force_time_index.index.name = 'Time (msec)'
# Linear interpolation to fill in NaN
df_interpolated_force = df_force_time_index.interpolate()
# Reset index so it can be used in plots
df_interpolated_force = df_interpolated_force.reset_index()

# Test
df_interpolated_rpm.plot(x='Time (msec)', y='rpm')
df_interpolated_force.plot(x='Time (msec)', y='Force(lbf)')