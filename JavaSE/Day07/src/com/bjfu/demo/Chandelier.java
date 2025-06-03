package com.bjfu.demo;

import lombok.Data;


public class Chandelier extends Appliance implements Switch{

    public static enum brightnessLevels {LOW, MEDIUM, HIGH};
    private brightnessLevels brightness;

     public Chandelier(String ModelNumber, boolean status, brightnessLevels brightness) {
        super(ModelNumber, status);
        if(status) {
            this.brightness = brightness;
        }
        else{
             this.brightness = null;
        }
    }

    public void Click() {
         System.out.println("（点击了开关）");
        if(isStatus()) {
            super.setStatus(false);
            this.brightness = null;
        }
        else {
            super.setStatus(true);
            this.brightness = brightnessLevels.LOW;
        }
    }
}
