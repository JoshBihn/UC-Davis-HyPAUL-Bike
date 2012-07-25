int32_t hydrogen_mass(float t_h2, int32_t p_h2) {
  // Remaining hydrogen mass estimation
  if (t_h2 > 0 && p_h2 > 0) {
    return roundf(p_h2*M_HYDROGEN_C/(t_h2+273.15));
  } else {
    return 0;
  }
}
