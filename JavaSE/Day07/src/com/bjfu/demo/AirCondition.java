package com.bjfu.demo;

import lombok.Data;

@Data

public class AirCondition extends Appliance implements  Switch{
    private int temperature;

     public AirCondition(String ModelNumber, boolean status, int temperature) {
        super(ModelNumber, status);
        if(status){
            this.temperature = temperature;
             System.out.println("The temperature is " + this.temperature);
        }
    }

    @Override
    public void Click() {
         System.out.println("（点击了开关）");
          if(isStatus()) {
            super.setStatus(false);
            this.temperature = 0;
        }
        else {
            super.setStatus(true);
            this.temperature = 25;
        }
    }
}
