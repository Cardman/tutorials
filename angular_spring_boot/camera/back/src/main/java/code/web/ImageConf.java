package code.web;

import code.gui.initialize.AbstractLightProgramInfos;
import code.maths.montecarlo.AbstractGenerator;
import code.vi.maths.random.AdvancedGenerator;
import code.vi.prot.impl.LigOtherProgramInfos;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

@Configuration
public class ImageConf {

    @Bean(name = "rd")
    public AbstractGenerator random() {
        return new AdvancedGenerator();
    }
    @Bean
    public AbstractLightProgramInfos light(@Autowired@Qualifier("rd") AbstractGenerator _gene) {
        return new LigOtherProgramInfos(_gene);
    }
}
