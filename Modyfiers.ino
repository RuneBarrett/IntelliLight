void dimMainHSV(int val) {
  if (val + mainColor.val > 255)
    mainColor.val = 255;
  else if (val + mainColor.val < 0)
    mainColor.val = 0;
  else
    mainColor.val += val;
}

