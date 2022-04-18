float julian_century, geom_mean_long_sun, geom_mean_anom_sun, eccent_earth_orbit, sun_app_long, obliq_corr, sun_declin, var_y, new_moon_phase_total;
extern float sunrise_time, sunset_time, new_moon_phase;

extern uint16_t curr_year;
extern uint8_t curr_month, curr_day, curr_hour_24, curr_min;
extern int UTC_offset;
extern long longitude, latitude;

void calc_times(void) {
  julian_century = ((367.0 * curr_year - int((7 * (curr_year + int((curr_month + 9) / 12.0))) / 4.0) + int((275 * curr_month) / 9.0) + curr_day + 1721013.5 + (curr_hour_24 - UTC_offset + curr_min / 60.0) / 24.0 - 0.5 * copysign(1, 100.0 * curr_year + curr_month - 190002.5) + 0.5) - 2451545.0) / 36525.0;
  geom_mean_long_sun = fmod(280.46646 + julian_century * (36000.76983 + julian_century * 0.0003032), 360);
  geom_mean_anom_sun = 357.52911 + julian_century * (35999.05029 - 0.0001537 * julian_century);
  eccent_earth_orbit = 0.016708634 - julian_century * (0.000042037 + 0.0000001267 * julian_century);
  sun_app_long = (geom_mean_long_sun + (sin(geom_mean_anom_sun * DEG_TO_RAD) * (1.914602 - julian_century * (0.004817 + 0.000014 * julian_century)) + sin(2 * geom_mean_anom_sun * DEG_TO_RAD) * (0.019993 - 0.000101 * julian_century) + sin(3 * geom_mean_anom_sun * DEG_TO_RAD) * 0.000289)) - 0.00569 - 0.00478 * sin(DEG_TO_RAD * (125.04 - 1934.136 * julian_century));
  obliq_corr = (23.0 + (26.0 + ((21.448 - julian_century * (46.815 + julian_century * (0.00059 - julian_century * 0.001813)))) / 60.0) / 60.0) + 0.00256 * cos(DEG_TO_RAD * (125.04 - 1934.136 * julian_century));
  var_y = tan(DEG_TO_RAD * obliq_corr / 2.0) * tan(DEG_TO_RAD * obliq_corr / 2.0);
  sunrise_time = ((720.0 - 4.0 * longitude - (4.0 * RAD_TO_DEG * (var_y * sin(2.0 * DEG_TO_RAD * geom_mean_long_sun) - 2.0 * eccent_earth_orbit * sin(DEG_TO_RAD * geom_mean_anom_sun) + 4.0 * eccent_earth_orbit * var_y * sin(DEG_TO_RAD * geom_mean_anom_sun) * cos(2.0 * DEG_TO_RAD * geom_mean_long_sun) - 0.5 * var_y * var_y * sin(4.0 * DEG_TO_RAD * geom_mean_long_sun) - 1.25 * eccent_earth_orbit * eccent_earth_orbit * sin(2.0 * DEG_TO_RAD * geom_mean_anom_sun))) + UTC_offset * 60.0) / 1440.0) - (RAD_TO_DEG * acos(cos(DEG_TO_RAD * 90.833) / (cos(DEG_TO_RAD * latitude) * cos(DEG_TO_RAD * (RAD_TO_DEG * asin(sin(DEG_TO_RAD * obliq_corr) * sin(DEG_TO_RAD * sun_app_long))))) - tan(DEG_TO_RAD * latitude) * tan(DEG_TO_RAD * (RAD_TO_DEG * asin(sin(DEG_TO_RAD * obliq_corr) * sin(DEG_TO_RAD * sun_app_long)))))) * 4.0 / 1440.0;
  sunset_time = ((720.0 - 4.0 * longitude - (4.0 * RAD_TO_DEG * (var_y * sin(2.0 * DEG_TO_RAD * geom_mean_long_sun) - 2.0 * eccent_earth_orbit * sin(DEG_TO_RAD * geom_mean_anom_sun) + 4.0 * eccent_earth_orbit * var_y * sin(DEG_TO_RAD * geom_mean_anom_sun) * cos(2.0 * DEG_TO_RAD * geom_mean_long_sun) - 0.5 * var_y * var_y * sin(4.0 * DEG_TO_RAD * geom_mean_long_sun) - 1.25 * eccent_earth_orbit * eccent_earth_orbit * sin(2.0 * DEG_TO_RAD * geom_mean_anom_sun))) + UTC_offset * 60.0) / 1440.0) + (RAD_TO_DEG * acos(cos(DEG_TO_RAD * 90.833) / (cos(DEG_TO_RAD * latitude) * cos(DEG_TO_RAD * (RAD_TO_DEG * asin(sin(DEG_TO_RAD * obliq_corr) * sin(DEG_TO_RAD * sun_app_long))))) - tan(DEG_TO_RAD * latitude) * tan(DEG_TO_RAD * (RAD_TO_DEG * asin(sin(DEG_TO_RAD * obliq_corr) * sin(DEG_TO_RAD * sun_app_long)))))) * 4.0 / 1440.0;
  
  new_moon_phase_total = ((367.0 * curr_year - int((7 * (curr_year + int((curr_month + 9) / 12.0))) / 4.0) + int((275 * curr_month) / 9.0) + curr_day + 1721013.5 + (curr_hour_24 - UTC_offset + curr_min / 60.0) / 24.0 - 0.5 * copysign(1, 100.0 * curr_year + curr_month - 190002.5) + 0.5) - 2451549.5) / 29.53;
  new_moon_phase = new_moon_phase_total - int(new_moon_phase_total);
  
}