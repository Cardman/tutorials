package code;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.core.annotation.Order;

@Configuration
@ComponentScan(basePackages = {"code"})
public class Config{

    public static final String SUM = "sum";
    public static final String MULT = "mult";
    public static final int SUM_INT = 0;
    public static final int MULT_INT = 1;

    @Bean(SUM)
    @Order(SUM_INT)
    public IntBean sum2() {
        return new SumBean();
    }

    @Bean(MULT)
    @Order(MULT_INT)
    public IntBean mult2() {
        return new ProdBean();
    }


}