package com.bjfu.demo;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.Getter;
import lombok.NoArgsConstructor;

@Data
@Getter
@NoArgsConstructor
@AllArgsConstructor

public class Appliance implements Switch{
     private String ModelNumber;
     private boolean status;

     @Override
     public void Click() {
          System.out.println("（点击了开关）");
           if(isStatus()) {
            setStatus(false);
        }
        else {
            setStatus(true);
        }
     }
}
