package upload;

import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.http.HttpHeaders;
import org.springframework.http.MediaType;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import org.springframework.web.servlet.mvc.method.annotation.StreamingResponseBody;

import org.springframework.core.io.InputStreamResource;
import javax.servlet.http.HttpServletResponse;

import code.stream.core.*;
import code.vi.sys.impl.*;

import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.io.*;
import java.util.concurrent.atomic.AtomicLong;
import java.util.concurrent.ConcurrentHashMap;
import java.util.Arrays;
import java.util.ArrayList;
import java.util.List;
import java.util.Collection;
import java.util.stream.Collectors;

import org.springframework.util.ResourceUtils;
import org.springframework.core.io.ClassPathResource;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Scope;
import org.springframework.context.annotation.ScopedProxyMode;


@Controller
public class FileUploader {

	@GetMapping(value = "/downloadlist")
    public ResponseEntity<byte[]> getSteamingFile() throws IOException {
		AbstractBinFact abs = new DefBinFact(new DefBinFactory(new SpringInputStreamBuilder()));
        byte[] isr = abs.loadFile("sample.txt");
        return ResponseEntity.ok()
		.header(HttpHeaders.CONTENT_DISPOSITION, "attachment;filename=" + "files.txt")
		.contentType(MediaType.APPLICATION_OCTET_STREAM)
		.body(isr);
    }

}
final class SpringInputStreamBuilder implements AbstractInputStreamBuilder {
    @Override
    public AbstractBinStreamIn build(String _fileName) {
        return new SpringBinStreamIn(_fileName);
    }
}
final class SpringBinStreamIn extends AbstractBinStreamInImpl {
    public SpringBinStreamIn(String _fileName) {
        super(tryCreateFileInputStream(_fileName));
    }

    public static InputStream tryCreateFileInputStream(String _fileName) {
        try {
			ClassPathResource res = new ClassPathResource(_fileName);
	        return res.getInputStream();
        } catch (Exception e) {
            return null;
        }
    }
}