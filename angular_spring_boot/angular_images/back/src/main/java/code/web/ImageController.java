package code.web;

import code.gui.images.AbstractImage;
import code.gui.images.ConverterGraphicBufferedImage;
import code.gui.initialize.AbstractLightProgramInfos;
import code.images.BaseSixtyFourUtil;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpHeaders;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.ArrayList;
import java.util.Base64;
import java.util.List;

@RestController
@RequestMapping({"/api"})
public class ImageController {

    @Autowired
    private AbstractLightProgramInfos lightProgramInfos;

    @PostMapping("/image")
    public Exported getImage(@RequestBody String image) {

        int[][] imageByString = BaseSixtyFourUtil.getImageByString(image);
        AbstractImage abstractImage_ = ConverterGraphicBufferedImage.decodeToImage(lightProgramInfos.getImageFactory(), imageByString);
        byte[] bytes = abstractImage_.writeImg("png");
        String encodeImage = Base64.getEncoder().withoutPadding().encodeToString(bytes);
        Exported exported = new Exported();
        exported.setImg(encodeImage);
        List<Byte> bytesList = new ArrayList<>();
        for (byte b: bytes) {
            bytesList.add(b);
        }
        exported.setBytes(bytesList);

        return exported;
    }

    @PostMapping("/bytes")
    public ResponseEntity<byte[]> getBytes(@RequestBody ExpFile image) {
        List<Byte> bytes = image.getBytes();
        int size = bytes.size();
        byte[] byteArray = new byte[size];
        for (int index = 0; index < size; index++) {
            byteArray[index] = bytes.get(index);
        }
        return ResponseEntity.ok()
                .header(HttpHeaders.CONTENT_DISPOSITION, "attachment;filename=" + image.getFileName())
                .contentType(MediaType.APPLICATION_OCTET_STREAM)
                .body(byteArray);
    }
}
