package code.web;

import code.gui.images.AbstractImage;
import code.gui.images.ConverterGraphicBufferedImage;
import code.gui.initialize.AbstractLightProgramInfos;
import code.images.BaseSixtyFourUtil;
import code.util.NonIterableBytes;
import code.util.core.StringUtil;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpHeaders;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import java.util.Base64;
import java.util.Collections;
import java.util.List;

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
    public List<ExportedDecode> getFiles(@RequestParam("file") MultipartFile mf) {
        return Collections.singletonList(apply(mf));
    }

    private ExportedDecode apply(MultipartFile f) {
        try {
            AbstractImage abstractImage = lightProgramInfos.getImageFactory().newImageFromBytes(f.getBytes());
            byte[] bytes = abstractImage.writeImg("png");
            String encodeImage = Base64.getEncoder().withoutPadding().encodeToString(bytes);
            ExportedDecode out = new ExportedDecode();
            Exported exported = new Exported();
            exported.setImg(encodeImage);
            exported.setBytes(NonIterableBytes.newCompositeList(bytes));
            int[][] pixels = ConverterGraphicBufferedImage.toArrays(abstractImage);
            out.setDecode(NonIterableBytes.newCompositeList(StringUtil.encode(BaseSixtyFourUtil.getStringByImage(pixels))));
            out.setExported(exported);
            return out;
        } catch (Exception e) {
            ExportedDecode out = new ExportedDecode();
            Exported exported = new Exported();
            exported.setImg("");
            exported.setBytes(NonIterableBytes.newCompositeList());
            out.setDecode(NonIterableBytes.newCompositeList());
            out.setExported(exported);
            return out;
        }
    }
}
