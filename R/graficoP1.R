library(readr)
library(scales)
library(ggplot2)

# leer datos
datos <- read_csv("datosp1c.csv")

## regresion lineal
fit = lm(log(y)~log(x), data=datos)
slope <- round(fit$coefficients["log(x)"],3)
error <- round(summary(fit)$coef[2,2],3)
r_squared = summary(fit)$r.squared
p_value = lmp(fit)

## graficar
p <-ggplot(datos,aes(x, y)) 
p + geom_point(size=2) + 
  ggtitle("Gráfico Log Log de Inserciones v/s Tiempo de Ejecución") +
  scale_x_continuous(trans='log10', name="Número de Inserciones",labels = comma,breaks = c(0,10,100,1000,10000,100000,1000000,10000000)) + 
  scale_y_continuous(trans='log10',name = "Tiempo de Ejecución (nanosegundos)",labels = comma) + 
  annotation_logticks() +
  theme_bw() +
  geom_boxplot(aes(group = x)) + 
  geom_smooth(method="lm") + 
  annotate("text",x=10000/2,y = 10000000, hjust=0,label = paste('R² = ', round(r_squared,3))) +
  annotate("text",x=10000/2,y = 1000000*5, hjust=0,label = paste('Valor p = ',formatC(p_value, format = "e", digits = 2))) +
  annotate("text",x=10000/2,y = 1000000*2.5, hjust=0,label = paste('Pendiente = ',slope, " ± ",error))


