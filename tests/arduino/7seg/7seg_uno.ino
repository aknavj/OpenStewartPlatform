/*
 */
int seg7_pins[7]= {
  2, // a
  3, // b
  4, // c
  5, // d
  6, // e
  7, // f
  8, // g
};

/*
 */
int seg7_digit[10][7] = {
  /* A    B     C     D     E     F     G */
  { LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  HIGH  }, // 0
  { HIGH, LOW,  LOW,  HIGH, HIGH, HIGH, HIGH  }, // 1
  { LOW,  LOW,  HIGH, LOW,  LOW,  HIGH, LOW   }, // 2
  { LOW,  LOW,  LOW,  LOW,  HIGH, HIGH, LOW   }, // 3
  { HIGH, LOW,  LOW,  HIGH, HIGH, LOW,  LOW   }, // 4
  { LOW,  HIGH, LOW,  LOW,  HIGH, LOW,  LOW   }, // 5
  { LOW,  HIGH, LOW,  LOW,  LOW,  LOW,  LOW   }, // 6
  { LOW,  LOW,  LOW,  HIGH, HIGH, HIGH, HIGH  }, // 7
  { LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW   }, // 8
  { LOW,  LOW,  LOW,  LOW,  HIGH,  LOW,  LOW  }, // 9
};

/* 
 */
void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(seg7_pins[i], OUTPUT);
  }
}

/*
 */
void segment_display(int num) {
   for (int i = 0; i < 7; i++) digitalWrite(seg7_pins[i], seg7_digit[num][i]);
}

/*
 */
void loop() {
  
  for (int i = 0; i < 10; i++ ) {
      segment_display(i);
      delay(1000);
  }
}
