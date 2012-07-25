int menu_page_id = 1;
unsigned long menu_next_refresh_time = 0;

void menu_refresh_due_now() {
  menu_next_refresh_time = 0;
}

void menu_next() {
  if (menu_page_id == MENU_PAGE_COUNT) {
      menu_page_id = 1;
  } else {
      menu_page_id++;
  }
  menu_refresh_due_now();
}

void menu_prev() {
  if (menu_page_id == 1) {
    menu_page_id = MENU_PAGE_COUNT;
  } else {
    menu_page_id--;
  }
  menu_refresh_due_now();
}

int menu_page(int id = -1) {
  if (id > -1) menu_page_id = id;
  return menu_page_id;
}

bool menu_refresh_due() {
  if (millis() > menu_next_refresh_time) {
    menu_next_refresh_time = millis()+MENU_REFR_TIME;
    return true;
  } else {
    return false;
  }
}



