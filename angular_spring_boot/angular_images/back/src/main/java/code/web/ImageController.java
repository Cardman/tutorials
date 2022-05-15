package code.web;

import code.gui.images.ConverterGraphicBufferedImage;
import code.gui.initialize.AbstractLightProgramInfos;
import code.images.BaseSixtyFourUtil;
import code.util.NonIterableBytes;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpHeaders;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import java.io.IOException;
import java.util.Base64;
import java.util.Collections;
import java.util.List;
import java.util.stream.Collectors;

@RestController
@RequestMapping({"/api"})
public class ImageController {

    @Autowired
    private AbstractLightProgramInfos lightProgramInfos;

    @PostMapping("/image")
    public Exported getImage(@RequestBody String image) {

        int[][] imageByString = BaseSixtyFourUtil.getImageByString(image);
        byte[] bytes = ConverterGraphicBufferedImage.decodeToImage(lightProgramInfos.getImageFactory(), imageByString).writeImg("png");
        String encodeImage = Base64.getEncoder().withoutPadding().encodeToString(bytes);
        Exported exported = new Exported();
        exported.setImg(encodeImage);
        exported.setBytes(NonIterableBytes.newCompositeList(bytes));

        return exported;
    }

    @PostMapping("/bytes")
    public ResponseEntity<byte[]> getBytes(@RequestBody ExpFile image) {
        byte[] byteArray = image.getBytes().toComposArrByte();
        return ResponseEntity.ok()
                .header(HttpHeaders.CONTENT_DISPOSITION, "attachment;filename=" + image.getFileName())
                .contentType(MediaType.APPLICATION_OCTET_STREAM)
                .body(byteArray);
    }

    @PostMapping("/doubledlist")
    public DoubledList getBytes(@RequestBody DoubledList image) {
        DoubledList doubledList = new DoubledList();
        doubledList.getStr().addAll(image.getStr());
        doubledList.getStr().addAll(image.getStr());
        return doubledList;
    }

    @PostMapping("/files")
    public List<Exported> getFiles(@RequestParam("file") MultipartFile mf) {
        return Collections.singletonList(apply(mf));
    }

    private Exported apply(MultipartFile f) {
        try {
            byte[] bytes = lightProgramInfos.getImageFactory().newImageFromBytes(f.getBytes()).writeImg("png");
            String encodeImage = Base64.getEncoder().withoutPadding().encodeToString(bytes);
            Exported exported = new Exported();
            exported.setImg(encodeImage);
            exported.setBytes(NonIterableBytes.newCompositeList(bytes));

            return exported;
        } catch (Exception e) {
            Exported exported = new Exported();
            exported.setImg("");
            exported.setBytes(NonIterableBytes.newCompositeList());
            return exported;
        }
    }
}
