int sd_error_id = 0;

char sd_file_name[12];

// file system object
SdFat sd_fs;

// file object
SdFile sd_file;

// buffered file writer
BufferedWriter sd_bw;

bool sd_new_file() {
  if (!sd_fs.init(SPI_FULL_SPEED)) {
    sd_error_id = 1;
    return 0;
  }

  strcpy(sd_file_name, "DATA000.CSV");

  for (uint8_t i = 0; i < 1000; i++) {
    sd_file_name[4] = i/100 + '0';
    sd_file_name[5] = i%100/10 + '0';
    sd_file_name[6] = i%10 + '0';
    if (sd_fs.exists(sd_file_name)) continue;
    sd_file.open(sd_file_name,  O_WRITE | O_CREAT | O_EXCL);
    sd_bw.init(&sd_file);
    break;
  }
  if (!sd_file.isOpen()) {
    sd_error_id = 2;
    return 0;
  }
  sd_error_id = 0;
  return 1;
}

bool sd_close_file() {
  sd_bw.writeBuf();
  return sd_file.close();
}

int sd_error() {
  return sd_error_id;
}

