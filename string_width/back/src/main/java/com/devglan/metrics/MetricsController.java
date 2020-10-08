package com.devglan.metrics;
import java.awt.*;
import java.awt.image.BufferedImage;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.Arrays;

@RestController
@RequestMapping({"/api"})
public class MetricsController {


    @GetMapping
    public String[] getFontsNames(){
        return GraphicsEnvironment.getLocalGraphicsEnvironment().getAvailableFontFamilyNames();
    }
    @PostMapping
    public int stringWidth(@RequestBody Metrics metrics){
        BufferedImage image = new BufferedImage(1, 1, BufferedImage.TYPE_INT_ARGB);
        Graphics2D g = image.createGraphics();
        Font f_;
        if (metrics.isBold()) {
            if (metrics.isItalic()) {
                f_ = new Font(metrics.getFont(),Font.BOLD+Font.ITALIC,metrics.getSize());
            } else {
                f_ = new Font(metrics.getFont(),Font.BOLD,metrics.getSize());
            }
        } else {
            if (metrics.isItalic()) {
                f_ = new Font(metrics.getFont(),Font.ITALIC,metrics.getSize());
            } else {
                f_ = new Font(metrics.getFont(),Font.PLAIN,metrics.getSize());
            }
        }
        FontMetrics fm = g.getFontMetrics(f_);
        return fm.stringWidth(metrics.getStr());
    }

}
