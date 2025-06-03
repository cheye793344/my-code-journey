package com.bjfu.demo;

import lombok.Data;

@Data

public class FloortoceilingWindow extends Appliance implements  Switch{
    @Override
    public void Click() {
        System.out.println("（点击了开关）");
          if(isStatus()) {
            super.setStatus(false);
            this.level = null;
        }
        else {
            super.setStatus(true);
            this.level = Level.VENT;
        }
    }

    //枚举三档开合程度
    public static enum Level{VENT,PARTIAL,FULLY};
    private Level level;
    public FloortoceilingWindow(String ModelNumber, boolean status, Level level) {
        super(ModelNumber, status);
        if(status) {
            this.level = level;
        }
        else{
            this.level = null;
        }
    }
}
