
int eyoubot_speed_control(CanInterface* device, uint8_t id, int speed );
int eyoubot_current_control(CanInterface* device, uint8_t id, int current);
int eyoubot_id(CanInterface* device, int new_id);
int eyoubot_baudrate(CanInterface* device, int baudrate);
int eyoubot_position_control(CanInterface* device, uint8_t id, int position, int speed);
int eyoubot_cease(CanInterface* device);

int eyoubot_get_current(CanInterface* device, uint8_t id );
int eyoubot_get_position(CanInterface* device, uint8_t id );
int eyoubot_get_speed(CanInterface* device, uint8_t id);
int eyoubot_get_temperature(CanInterface* device, uint8_t id);

int eyoubot_limit_current(CanInterface* device, uint8_t id, int current);
int eyoubot_limit_speed(CanInterface* device, uint8_t id, int speed_limit);

int eyoubot_limit_upper_position(CanInterface* device, uint8_t id, int upper_limit);
int eyoubot_limit_lower_position(CanInterface* device, uint8_t id, int lower_limit);