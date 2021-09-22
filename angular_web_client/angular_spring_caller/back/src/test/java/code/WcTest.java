package code;

import okhttp3.mockwebserver.MockResponse;
import okhttp3.mockwebserver.MockWebServer;
import org.junit.jupiter.api.Test;
import org.springframework.web.reactive.function.client.WebClient;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class WcTest {

    @Test
    public void sum() throws Exception {
        MockWebServer mockBackEnd = new MockWebServer();
        mockBackEnd.start();
        String baseUrl = String.format("http://localhost:%s",
                mockBackEnd.getPort());
        WebClient webClient = WebClient.create(baseUrl);
        SecController secController = new SecController(webClient);
        mockBackEnd.enqueue(new MockResponse()
                .setBody("2")
                .addHeader("Content-Type", "application/json"));
        assertEquals(2L,secController.oper(0,1,1).longValue());
        mockBackEnd.shutdown();
    }
}
