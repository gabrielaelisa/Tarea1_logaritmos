library(readr)
library(scales)
library(ggplot2)
library(ggthemes)

# leer datos
datos_ord <- read_csv("datosp1cordenamiento.csv")

## regresion lineal
fit = lm(y~x, data=datos_ord)
slope <- round(fit$coefficients["x"],1)
error <- round(summary(fit)$coef[2,2],1)

## graficar
p <-ggplot(datos_ord,aes(x, y)) 
p + geom_point(size=2) + 
  ggtitle("Gráfico log log de Inserciones vs Tiempo de Ejecución") +
  scale_x_continuous(trans='log10', name="Número de Inserciones",labels = comma,breaks = c(0,10,100,1000,10000,100000,1000000,10000000)) + 
  scale_y_continuous(trans='log10',name = "Tiempo de Ejecución (nanosegundos)",labels = comma) + 
  annotation_logticks() +
  theme_bw() +
  geom_boxplot(aes(group = x)) + 
  geom_smooth(method="lm") + 
  annotate("text",x=10000/3,y = 10000000, hjust=0,label = paste('Correlación = ', round(cor(datos_ord$x, datos_ord$y),2))) +
  annotate("text",x=10000/3,y = 1000000*5, hjust=0,label = paste('Pendiente = ',slope, " ± ",error))


