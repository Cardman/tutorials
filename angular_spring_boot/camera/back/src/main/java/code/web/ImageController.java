package code.web;

import code.gui.GuiConstants;
import code.gui.images.AbstractImage;
import code.gui.initialize.AbstractLightProgramInfos;
import code.util.NonIterableBytes;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.Base64;

@RestController
@RequestMapping({"/api"})
public class ImageController {

    @Autowired
    private AbstractLightProgramInfos lightProgramInfos;

    @PostMapping("/image")
    public Exported getImage(@RequestBody Coords coords) {

        int h=9;
        int w=9;
        int cx = w/2;
        int cy = h/2;
        int sq = 32;
        AbstractImage abstractImage = lightProgramInfos.getImageFactory().newImageArgb(w * sq, h * sq);
        abstractImage.setColor(GuiConstants.BLACK);
        abstractImage.fillRect(0,0, abstractImage.getWidth(), abstractImage.getHeight());
        int x = coords.getX();
        int y = coords.getY();
        System.out.println(x+","+y);
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < h; j++) {
                abstractImage.setColor(GuiConstants.WHITE);
                int dx = i-x;
                int dy = j-y;
                abstractImage.drawRect(sq*i,sq*j, sq, sq);
                abstractImage.drawString((dx-cx)+" "+(dy-cy),sq*i,sq*j+16);
            }
        }
        byte[] bytes = abstractImage.writeImg("png");
        abstractImage.dispose();
        String encodeImage = Base64.getEncoder().withoutPadding().encodeToString(bytes);
        Exported exported = new Exported();
        exported.setImg(encodeImage);
        exported.setBytes(NonIterableBytes.newCompositeList(bytes));

        return exported;
    }


}
