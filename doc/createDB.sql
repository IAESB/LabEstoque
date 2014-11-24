SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

-- -----------------------------------------------------
-- Schema lab_estoque
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `lab_estoque` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci ;
USE `lab_estoque` ;

-- -----------------------------------------------------
-- Table `lab_estoque`.`grupo`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `lab_estoque`.`grupo` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `nome` VARCHAR(45) NULL,
  `grupo_id` INT NULL,
  PRIMARY KEY (`id`),
  INDEX `fk_grupo_grupo1_idx` (`grupo_id` ASC),
  CONSTRAINT `fk_grupo_grupo1`
    FOREIGN KEY (`grupo_id`)
    REFERENCES `lab_estoque`.`grupo` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `lab_estoque`.`material`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `lab_estoque`.`material` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `nome` VARCHAR(45) NULL,
  `descricao` VARCHAR(45) NULL,
  `imagem` BLOB NULL,
  `quantidade` INT NULL,
  `grupo_id` INT NULL,
  PRIMARY KEY (`id`),
  INDEX `fk_reagente_grupo_idx` (`grupo_id` ASC),
  CONSTRAINT `fk_reagente_grupo`
    FOREIGN KEY (`grupo_id`)
    REFERENCES `lab_estoque`.`grupo` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `lab_estoque`.`usuario`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `lab_estoque`.`usuario` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `nome` VARCHAR(45) NULL,
  `senha` VARCHAR(45) NULL,
  PRIMARY KEY (`id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `lab_estoque`.`laboratorio`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `lab_estoque`.`laboratorio` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `nome` VARCHAR(45) NULL,
  PRIMARY KEY (`id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `lab_estoque`.`solicitante`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `lab_estoque`.`solicitante` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `nome` VARCHAR(45) NULL,
  `matricula` VARCHAR(45) NULL,
  PRIMARY KEY (`id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `lab_estoque`.`saida`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `lab_estoque`.`saida` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `data` TIMESTAMP NULL,
  `laboratorio_id` INT NOT NULL,
  `solicitante_id` INT NOT NULL,
  `usuario_id` INT NULL,
  PRIMARY KEY (`id`),
  INDEX `fk_consumo_usuario1_idx` (`usuario_id` ASC),
  INDEX `fk_consumo_laboratorio1_idx` (`laboratorio_id` ASC),
  INDEX `fk_saida_solicitante1_idx` (`solicitante_id` ASC),
  CONSTRAINT `fk_consumo_usuario1`
    FOREIGN KEY (`usuario_id`)
    REFERENCES `lab_estoque`.`usuario` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_consumo_laboratorio1`
    FOREIGN KEY (`laboratorio_id`)
    REFERENCES `lab_estoque`.`laboratorio` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_saida_solicitante1`
    FOREIGN KEY (`solicitante_id`)
    REFERENCES `lab_estoque`.`solicitante` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `lab_estoque`.`entrada`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `lab_estoque`.`entrada` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `data` TIMESTAMP NULL,
  `fornecedor` VARCHAR(45) NULL,
  `anotacao` TEXT NULL,
  `usuario_id` INT NULL,
  PRIMARY KEY (`id`),
  INDEX `fk_entrada_usuario1_idx` (`usuario_id` ASC),
  CONSTRAINT `fk_entrada_usuario1`
    FOREIGN KEY (`usuario_id`)
    REFERENCES `lab_estoque`.`usuario` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `lab_estoque`.`lote`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `lab_estoque`.`lote` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `nome` VARCHAR(45) NULL,
  `validade` TIMESTAMP NULL,
  `quantidade` INT NULL,
  PRIMARY KEY (`id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `lab_estoque`.`entrada_de_material`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `lab_estoque`.`entrada_de_material` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `entrada_id` INT NOT NULL,
  `material_id` INT NOT NULL,
  `lote_id` INT NULL,
  `valor` DECIMAL NULL,
  `quantidade` INT NULL,
  PRIMARY KEY (`id`, `entrada_id`, `material_id`),
  INDEX `fk_entrada_has_material_material1_idx` (`material_id` ASC),
  INDEX `fk_entrada_has_material_entrada1_idx` (`entrada_id` ASC),
  INDEX `fk_entrada_de_material_lote1_idx` (`lote_id` ASC),
  CONSTRAINT `fk_entrada_has_material_entrada1`
    FOREIGN KEY (`entrada_id`)
    REFERENCES `lab_estoque`.`entrada` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_entrada_has_material_material1`
    FOREIGN KEY (`material_id`)
    REFERENCES `lab_estoque`.`material` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_entrada_de_material_lote1`
    FOREIGN KEY (`lote_id`)
    REFERENCES `lab_estoque`.`lote` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `lab_estoque`.`saida_de_material`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `lab_estoque`.`saida_de_material` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `saida_id` INT NOT NULL,
  `material_id` INT NOT NULL,
  `lote_id` INT NULL,
  `quantidade` INT NULL,
  PRIMARY KEY (`id`, `saida_id`, `material_id`),
  INDEX `fk_saida_has_material_material1_idx` (`material_id` ASC),
  INDEX `fk_saida_has_material_saida1_idx` (`saida_id` ASC),
  INDEX `fk_saida_de_material_lote1_idx` (`lote_id` ASC),
  CONSTRAINT `fk_saida_has_material_saida1`
    FOREIGN KEY (`saida_id`)
    REFERENCES `lab_estoque`.`saida` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_saida_has_material_material1`
    FOREIGN KEY (`material_id`)
    REFERENCES `lab_estoque`.`material` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_saida_de_material_lote1`
    FOREIGN KEY (`lote_id`)
    REFERENCES `lab_estoque`.`lote` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `lab_estoque`.`pesquisa`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `lab_estoque`.`pesquisa` (
  `id` INT(11) NOT NULL AUTO_INCREMENT,
  `nome` VARCHAR(45) NULL DEFAULT NULL,
  `data_inicial` TIMESTAMP NULL DEFAULT NULL,
  `data_fianal` TIMESTAMP NULL DEFAULT NULL,
  `isEntrada` TINYINT(1) NULL DEFAULT NULL,
  `isSaida` TINYINT(1) NULL DEFAULT NULL,
  `materiais` TINYTEXT NULL DEFAULT NULL,
  `quantidadeMaterialDe` INT(11) NULL DEFAULT NULL,
  `quantidadeMaterialAte` INT(11) NULL DEFAULT NULL,
  `lote` VARCHAR(45) NULL DEFAULT NULL,
  `validadade` VARCHAR(45) NULL DEFAULT NULL,
  `valor` VARCHAR(45) NULL DEFAULT NULL,
  `quantidadeEntradaDe` INT(11) NULL DEFAULT NULL,
  `quantidadeEntradaAte` INT(11) NULL DEFAULT NULL,
  `quantidadeSaidaDe` INT(11) NULL DEFAULT NULL,
  `quantidadeSaidaAte` INT(11) NULL,
  `laboratorio` VARCHAR(45) NULL,
  `solicitante` VARCHAR(45) NULL,
  `usuario_id` INT NULL,
  PRIMARY KEY (`id`),
  INDEX `fk_pesquisa_usuario1_idx` (`usuario_id` ASC),
  CONSTRAINT `fk_pesquisa_usuario1`
    FOREIGN KEY (`usuario_id`)
    REFERENCES `lab_estoque`.`usuario` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
