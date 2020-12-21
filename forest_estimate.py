import pandas as pd
from sklearn.ensemble import RandomForestRegressor


def divide_train_data_as_test_data(seconds_df, test_sample_size=0.2):
    """
    学習データとテストデータに分ける
    :param test_sample_size: 何％をテストデータとするか
    :param seconds_df: 生データから"time", ".速度"列を除いたもの
    :return:
    """
    test_data = seconds_df.sample(frac=test_sample_size, random_state=1)
    train_data = seconds_df.drop(test_data.index)
    return test_data, train_data


def creation_feature_and_target(split_df, target_col_name="theta", unnecessary_col_list=None):
    if unnecessary_col_list is None:
        unnecessary_col_list = ["time", "speed"]
    drop_col_list = [target_col_name] + unnecessary_col_list
    return split_df[target_col_name], split_df.drop(drop_col_list, axis=1)


def save_train_test_data_to_file(train_data, test_data, file_directory,
                                 train_data_name="train.csv",
                                 test_data_name="test.csv"):
    """
    example:
    code: save_train_test_data_to_file(train_df, test_df, file_directory="data/", train_data_name="study_data.csv")
    result: 「data」ファイルに学習データを「study_data.csv」という名前で保存
    :param train_data:
    :param test_data:
    :param file_directory: 保存したいファイルの相対パス
    :param train_data_name: 学習データの保存名 *.csvが必須
    :param test_data_name: テストデータの保存名 *.csvが必須
    :return: none
    """
    train_file_name = file_directory + train_data_name
    test_file_name = file_directory + test_data_name
    train_data.to_csv(train_file_name, index=False)
    test_data.to_csv(test_file_name, index=False)


if __name__ == '__main__':
    # データのインポート 相対パスとファイル名でデータ指定
    raw_df = pd.read_csv("data/raw_motor_data.csv")
    # 学習データとテストデータの作成
    test_df, train_df = divide_train_data_as_test_data(seconds_df=raw_df)
    test_target_df, test_feature_df = creation_feature_and_target(test_df)
    train_target_df, train_feature_df = creation_feature_and_target(train_df)
    # 学習に不要な列削除

    # 学習
    regression_machine = RandomForestRegressor()
    regression_machine.fit(train_feature_df, train_target_df)
    prediction_train_df = regression_machine.predict(train_feature_df)
    prediction_test_df = regression_machine.predict(test_feature_df)
    # データの保存
    train_df["estimate_theta"] = prediction_train_df
    test_df["estimate_theta"] = prediction_test_df
    save_train_test_data_to_file(train_df, test_df, file_directory="data/forest_estimate/")  # 詳しくは関数参照
