package code.web;

import code.gui.images.AbstractImage;
import code.gui.images.ConverterGraphicBufferedImage;
import code.gui.initialize.AbstractLightProgramInfos;
import code.images.BaseSixtyFourUtil;
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
    public Exported getImage(@RequestBody String image) {

        int[][] imageByString = BaseSixtyFourUtil.getImageByString(image);
        AbstractImage abstractImage_ = ConverterGraphicBufferedImage.decodeToImage(lightProgramInfos.getImageFactory(), imageByString);
        String encodeImage = Base64.getEncoder().withoutPadding().encodeToString(abstractImage_.writeImg("png"));
        Exported exported = new Exported();
        exported.setImg(encodeImage);

        return exported;
    }
}
